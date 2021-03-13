#include "event.h"
#include "net.h"
#include "config.h"
#include "log.h"
#include "connection.h"


static void close_accepted_connection(connection_t *c);
ssize_t unix_recv(connection_t *c, u_char *buf, size_t size);
ssize_t unix_send(connection_t *c, u_char *buf, size_t size);

void event_accept(event_t *ev)
{
    log_info(NET->log,"event: event_accept");
    socklen_t          socklen;
    socket_t       s;
    listening_t   *ls;
    connection_t  *c, *lc;
    u_char             sa[SOCKADDRLEN];
    int err;
    int               reuseaddr = 1;

    static uint_t  use_accept4 = 1;

    //表示尽可能多次调用accept 获取新连接
    ev->available = 1;

    lc = ev->data;
    ls = lc->listening;
    ev->ready = 0;

    // do {
        socklen = SOCKADDRLEN;

        if (use_accept4) {
            s = accept4(lc->fd, (struct sockaddr *) sa, &socklen,
                        SOCK_NONBLOCK);
        } else {
            s = accept(lc->fd, (struct sockaddr *) sa, &socklen);
        }

        if (s == -1) {
            err = errno;

            if (err == EAGAIN) {
                return;
            }
            return;
        }

        c = get_connection(s);

        if (c == NULL) {
            if (close(s) == -1) {
                printf("close socket failed\n");
            }
            return;
        }

        c->sockaddr = gc_malloc(socklen);
        if (c->sockaddr == NULL) {
            close_accepted_connection(c);
            return;
        }
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,(const void *) &reuseaddr, sizeof(int)) == -1)
        {
            if (close_socket(s) == -1) {
            }

            return;
        }
        memcpy(c->sockaddr, sa, socklen);
        // if (!(event_flags & (USE_AIO_EVENT|USE_RTSIG_EVENT))) {
        if (nonblocking(s) == -1) {
            printf("alert ev->log nonblocking_n failed\n");
            close_accepted_connection(c);
            return;
        }
        // }

        c->recv = unix_recv;
        c->send = unix_send;


        c->socklen = socklen;
        c->listening = ls;
        c->local_sockaddr = ls->sockaddr;

        // c->read->ready = 1;
        c->write->ready = 1;


        log_info(c->log,"fd:%d accept:",s);
        if (add_conn && (event_flags & USE_EPOLL_EVENT) == 0) {
            if (add_conn(c) == ERROR) {
                close_accepted_connection(c);
                return;
            }
        }
        ls->handler(c);

    // } while (ev->available);
}

ssize_t unix_recv(connection_t *c, u_char *buf, size_t size)
{
    ssize_t       n;
    event_t  *rev;
    int  err;

    rev = c->read;
    do {
        n = recv(c->fd, buf, size, 0);
        log_info(c->log,"recv: fd:%d %d of %d",c->fd,n,size);
        if (n == 0) {
            rev->ready = 0;
            rev->eof = 1;

        }

        if (n > 0) {
            log_info(c->log,"unix_recv: n > 0 :%d ",n);
            if ((size_t) n < size
                && !(event_flags & USE_GREEDY_EVENT))
            {
                rev->ready = 0;
            }

            return n;
        }

        err = errno;

        if (err == EAGAIN || err == EINTR) {
            n = AGAIN;

        } else {
            log_error(c->log,"recv() failed");
            // n = connection_error(c, err, "recv() failed");
            break;
        }

    } while (err == EINTR);

    rev->ready = 0;

    if (n == ERROR) {
        rev->error = 1;
    }

    return n;
}
ssize_t unix_send(connection_t *c, u_char *buf, size_t size)
{
    ssize_t       n;
    int     err;
    event_t  *wev;

    wev = c->write;


    for ( ;; ) {
        n = send(c->fd, buf, size, 0);

        if (n > 0) {
            if (n < (ssize_t) size) {
                wev->ready = 0;
            }

            c->sent += n;

            return n;
        }

        err = errno;

        if (n == 0) {
            wev->ready = 0;
            return n;
        }

        if (err == EAGAIN || err == EINTR) {
            wev->ready = 0;

            if (err == EAGAIN) {
                return AGAIN;
            }

        } else {
            wev->error = 1;
            // (void) connection_error(c, err, "send() failed");
            log_error(c->log,"send() failed");
            return ERROR;
        }
    }
}

static void
close_accepted_connection(connection_t *c)
{
    socket_t  fd;

    free_connection(c);

    fd = c->fd;
    c->fd = (socket_t) -1;

    if (close(fd) == -1) {
    }

}

