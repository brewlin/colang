#include "config.h"
#include "event.h"
#include "connection.h"
#include "net.h"
#include "log.h"

typedef intptr_t        int_t;
typedef uintptr_t       uint_t;

static int_t epoll_init(net_t *net,int_t events);
static void epoll_done(net_t *net);
static int_t epoll_add_event(event_t *ev, int_t event,
    uint_t flags);
static int_t epoll_del_event(event_t *ev, int_t event,
    uint_t flags);
static int_t epoll_add_connection(connection_t *c);
static int_t epoll_del_connection(connection_t *c,
    uint_t flags);
static int_t epoll_process_events(net_t *net,uint_t flags);

event_actions_t event_actions =     {
        epoll_add_event,             /* add an event */
        epoll_del_event,             /* delete an event */
        epoll_add_event,             /* enable an event */
        epoll_del_event,             /* disable an event */
        epoll_add_connection,        /* add an connection */
        epoll_del_connection,        /* delete an connection */
        NULL,                            /* process the changes */
        epoll_process_events,        /* process the events */
        epoll_init,                  /* init the events */
        epoll_done,                  /* done the events */
};


static int                  ep = -1;
static struct epoll_event  *event_list;
static uint_t               nevents;

//初始化创建 epoll 结构体和 对于事件列表内存
//events 对应有多少个事件列表
static int_t epoll_init(net_t *net,int_t events)
{
    log_info(net->log,"event: epoll init");

    if (ep == -1) {
        ep = epoll_create(net->connection_n / 2);

        if (ep == -1) {
            printf("epoll_create failed\n");
            return ERROR;
        }

    }

    if (nevents < events) {
        if (event_list) {
            free(event_list);
        }

        event_list = gc_malloc(sizeof(struct epoll_event) * events);
        if (event_list == NULL) {
            return ERROR;
        }
    }

    nevents = events;

    event_flags = USE_CLEAR_EVENT // epoll ET模式
                  |USE_GREEDY_EVENT
                  |USE_EPOLL_EVENT;

    return OK;
}

static void
epoll_done(net_t *net)
{
    if (close(ep) == -1) {
        printf("epoll close failed\n");
    }

    ep = -1;

    free(event_list);

    event_list = NULL;
    nevents = 0;
}


static int_t
epoll_add_event(event_t *ev, int_t event, uint_t flags)
{
    int                  op;
    uint32_t             events, prev;
    event_t         *e;
    connection_t    *c;
    struct epoll_event   ee;

    c = ev->data;

    events = (uint32_t) event;

    if (event == READ_EVENT) {
        e = c->write;
        prev = EPOLLOUT;
        events = EPOLLIN;
    } else {
        e = c->read;
        prev = EPOLLIN;
        events = EPOLLOUT;
    }

    if (e->active) {
        op = EPOLL_CTL_MOD;
        events |= prev;

    } else {
        op = EPOLL_CTL_ADD;
    }

    ee.events = events | (uint32_t) flags;
    ee.data.ptr = (void *) ((uintptr_t) c | ev->instance);
    log_info(c->log,"epoll add event %d ",c->fd);

    if (epoll_ctl(ep, op, c->fd, &ee) == -1) {
        log_error(c->log,"epoll_ctl %d failed\n",c->fd);
        return ERROR;
    }

    ev->active = 1;
    return OK;
}


static int_t
epoll_del_event(event_t *ev, int_t event, uint_t flags)
{
    int                  op;
    uint32_t             prev;
    event_t         *e;
    connection_t    *c;
    struct epoll_event   ee;

    /*
     * when the file descriptor is closed, the epoll automatically deletes
     * it from its queue, so we do not need to delete explicity the event
     * before the closing the file descriptor
     */

    if (flags & CLOSE_EVENT) {
        ev->active = 0;
        return OK;
    }

    c = ev->data;

    if (event == READ_EVENT) {
        e = c->write;
        prev = EPOLLOUT;

    } else {
        e = c->read;
        prev = EPOLLIN;
    }

    if (e->active) {
        op = EPOLL_CTL_MOD;
        ee.events = prev | (uint32_t) flags;
        ee.data.ptr = (void *) ((uintptr_t) c | ev->instance);

    } else {
        op = EPOLL_CTL_DEL;
        ee.events = 0;
        ee.data.ptr = NULL;
    }

    log_info(c->log,"epoll_ctl %d",c->fd);
    if (epoll_ctl(ep, op, c->fd, &ee) == -1) {
        log_error(c->log,"epoll_ctl :%d failed",c->fd);
        return ERROR;
    }

    ev->active = 0;

    return OK;
}


static int_t
epoll_add_connection(connection_t *c)
{
    struct epoll_event  ee;

    ee.events = EPOLLIN|EPOLLOUT|EPOLLET;
    ee.data.ptr = (void *) ((uintptr_t) c | c->read->instance);

    log_info(c->log,"epoll add connection fd:%d",c->fd);
    if (epoll_ctl(ep, EPOLL_CTL_ADD, c->fd, &ee) == -1) {
        log_error(c->log,"epoll add connection fd:%d failed",c->fd);
        return ERROR;
    }

    c->read->active = 1;
    c->write->active = 1;

    return OK;
}


static int_t
epoll_del_connection(connection_t *c, uint_t flags)
{
    int                 op;
    struct epoll_event  ee;

    /*
     * when the file descriptor is closed the epoll automatically deletes
     * it from its queue so we do not need to delete explicity the event
     * before the closing the file descriptor
     */

    if (flags & CLOSE_EVENT) {
        c->read->active = 0;
        c->write->active = 0;
        return OK;
    }

    log_info(c->log,"del connection event");

    op = EPOLL_CTL_DEL;
    ee.events = 0;
    ee.data.ptr = NULL;

    if (epoll_ctl(ep, op, c->fd, &ee) == -1) {
        printf("del connection failed");
        return ERROR;
    }

    c->read->active = 0;
    c->write->active = 0;

    return OK;
}


static int_t
epoll_process_events(net_t *net, uint_t flags)
{
    int                events;
    uint32_t           revents;
    int_t          instance, i;
    err_t          err;
    event_t       *rev, *wev;
    connection_t  *c;

    /* TIMER_INFINITE == INFTIM */

    // log_debug1(LOG_DEBUG_EVENT, net->log, 0,
                //    "epoll timer: %M", timer);

    events = epoll_wait(ep, event_list, (int) nevents, 10 * 1000);

    err = (events == -1) ? errno : 0;

    if (err) {
        log_error(net->log,"epoll_wait() failed");
        return ERROR;
    }

    if (events == 0) {
        log_error(net->log,"epoll_wait() returned no events without timeout");
        return AGAIN;
    }


    for (i = 0; i < events; i++) {
        c = event_list[i].data.ptr;

        instance = (uintptr_t) c & 1;
        c = (connection_t *) ((uintptr_t) c & (uintptr_t) ~1);

        rev = c->read;

        if (c->fd == -1 || rev->instance != instance) {

            continue;
        }

        revents = event_list[i].events;



        if ((revents & (EPOLLERR|EPOLLHUP))
             && (revents & (EPOLLIN|EPOLLOUT)) == 0)
        {
            /*
             * if the error events were returned without EPOLLIN or EPOLLOUT,
             * then add these flags to handle the events at least in one
             * active handler
             */

            revents |= EPOLLIN|EPOLLOUT;
        }

        if ((revents & EPOLLIN) && rev->active) {
            rev->ready = 1;
            rev->handler(rev);
        }

        wev = c->write;

        if ((revents & EPOLLOUT) && wev->active) {

            if (c->fd == -1 || wev->instance != instance) {

                /*
                 * the stale event from a file descriptor
                 * that was just closed in this iteration
                 */
                continue;
            }

            wev->ready = 1;
            wev->handler(wev);
        }
    }
    return OK;
}


