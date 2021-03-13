#include "connection.h"
#include "config.h"
#include "net.h"
#include "event.h"
#include "log.h"

listening_t *create_listening(net_t *net, void *sockaddr, socklen_t socklen)
{
    listening_t  *ls,*lp;
    struct sockaddr  *sa;

    ls = gc_malloc(sizeof(listening_t));
    if (ls == NULL) {
        return NULL;
    }
    memzero(ls, sizeof(listening_t));


    sa = gc_malloc(socklen);
    if (sa == NULL) {
        return NULL;
    }
    memcpy(sa, sockaddr, socklen);
    ls->sockaddr = sa;
    ls->socklen = socklen;

    ls->fd = (socket_t) -1;
    ls->type = SOCK_STREAM;

    ls->backlog = BACKLOG;
    ls->rcvbuf = -1;
    ls->sndbuf = -1;

    //追加到全局net->listening 链表上去
    if(net->listening == NULL) net->listening = ls;
    else{
        lp = net->listening;
        while(lp->next != NULL) lp = lp->next;
        lp->next = ls;
    }

    return ls;
}


int_t open_listening_sockets(net_t *net)
{
    int               reuseaddr;
    uint_t           tries, failed;
    socket_t      s;
    listening_t  *ls;

    reuseaddr = 1;

    /* TODO: configurable try number */

    for (tries = 2; tries; tries--) {
        failed = 0;

        /* for each listening socket */
        ls = net->listening;
        while(ls != NULL){
            if (ls->ignore || ls->fd != -1) {
                ls = ls->next;
                continue;
            }

            s = socket(ls->sockaddr->sa_family, ls->type, 0);
            if(s == -1){
                log_info(net->log, "socket failed: %s ", strerror(errno));
                return ERROR;
            }
            log_info(net->log, "socket success: %s", strerror(errno));

            if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,(const void *) &reuseaddr, sizeof(int)) == -1)
            {
                if (close_socket(s) == -1) {
                }

                return ERROR;
            }
            log_info(net->log, "setsockopt success: %s", strerror(errno));

            /* TODO: close on exit */

            // if (!(event_flags & USE_AIO_EVENT)) {
                if (nonblocking(s) == -1) {
                    if (close_socket(s) == -1) {
                    }

                    return ERROR;
                }
                log_info(net->log, "nonblocking success: %s", strerror(errno));
            // }

            if(bind(s, ls->sockaddr, ls->socklen) == -1) {
                log_error(net->log, "bind: %s", strerror(errno));

                if (close_socket(s) == -1) {
                }

                failed = 1;
                ls = ls->next;
                continue;
            }
            log_info(net->log, "bind success: %s", strerror(errno));


            if (listen(s, ls->backlog) == -1) {
                log_error(net->log, "listen: %s", strerror(errno));

                if (close_socket(s) == -1) {
                }

                return ERROR;
            }

            ls->listen = 1;
            ls->fd = s;
            msleep(500);
            ls = ls->next;
        }

        if (!failed) {
            break;
        }

        /* TODO: delay configurable */
        log_info(net->log,"try again to bind() after 500ms");
    }

    if (failed) {
        log_error(net->log,"still could not bind");
        return ERROR;
    }

    return OK;
}


void close_listening_sockets(net_t *net)
{
    listening_t   *ls;
    connection_t  *c;


    ls = net->listening;
    while(ls != NULL)
    {
        c = ls->connection;

        if (c) {
            if (c->read->active) {


                    /*
                     * it seems that Linux-2.6.x OpenVZ sends events
                     * for closed shared listening sockets unless
                     * the events was explicity deleted
                     */

                del_event(c->read, READ_EVENT, 0);
            }

            free_connection(c);

            c->fd = (socket_t) -1;
        }

        log_info(c->log,"close listening #%d ", ls->fd);

        if (close(ls->fd) == -1) {
            log_info(c->log,"close listening #%d failed", ls->fd);
        }
        ls->fd = (socket_t) -1;
        ls = ls->next;
    }
}


connection_t *get_connection(socket_t s)
{
    uint_t         instance;
    event_t       *rev, *wev;
    connection_t  *c;

    c = NET->free_connections;
    if (c == NULL) {
        log_error(NET->log,"%d worker_connections are not enough", NET->connection_n);
        return NULL;
    }

    NET->free_connections = c->data;
    NET->free_connection_n--;

    rev = c->read;
    wev = c->write;

    memzero(c, sizeof(connection_t));

    c->read = rev;
    c->write = wev;
    c->fd = s;
    c->log = NET->log;

    instance = rev->instance;

    memzero(rev, sizeof(event_t));
    memzero(wev, sizeof(event_t));

    rev->instance = !instance;
    wev->instance = !instance;

    rev->data = c;
    wev->data = c;

    wev->write = 1;

    return c;
}


void
free_connection(connection_t *c)
{
    net_t *net = NET;

    c->data = net->free_connections;
    net->free_connections = c;
    net->free_connection_n++;
}


void
close_connection(connection_t *c)
{
    socket_t  fd;

    if (c->fd == -1) {
        log_error(c->log, "connection already closed");
        return;
    }

    if (del_conn) {
        del_conn(c, CLOSE_EVENT);

    } else {
        if (c->read->active) {
            del_event(c->read, READ_EVENT, CLOSE_EVENT);
        }

        if (c->write->active) {
            del_event(c->write, WRITE_EVENT, CLOSE_EVENT);
        }
    }

    free_connection(c);

    fd = c->fd;
    c->fd = (socket_t) -1;

    if (close_socket(fd) == -1) {
        log_error(c->log,"close socket failed");
    }
}
