#ifndef _EVENT_H_INCLUDED_
#define _EVENT_H_INCLUDED_

#include "config.h"
#include "connection.h"
#include <sys/epoll.h>

#define INVALID_INDEX  0xd0d0d0d0



struct event_s {
    void            *data;

    unsigned         write:1;

    unsigned         accept:1;

    /* used to detect the stale events in kqueue, rtsig, and epoll */
    unsigned         instance:1;

    /*
     * the event was passed or would be passed to a kernel;
     * in aio mode - operation was posted.
     */
    unsigned         active:1;

    /* the ready event; in aio mode 0 means that no operation can be posted */
    unsigned         ready:1;

    unsigned         eof:1;
    unsigned         error:1;
    unsigned         available:1;
    unsigned         closed:1;

    event_handler_pt  handler;

    /* the links of the posted queue */
    event_t     *next;
    event_t    **prev;
    log_t       *log;

};

typedef struct {
    int_t  (*add)(event_t *ev, int_t event, uint_t flags);
    int_t  (*del)(event_t *ev, int_t event, uint_t flags);

    int_t  (*enable)(event_t *ev, int_t event, uint_t flags);
    int_t  (*disable)(event_t *ev, int_t event, uint_t flags);

    int_t  (*add_conn)(connection_t *c);
    int_t  (*del_conn)(connection_t *c, uint_t flags);

    int_t  (*process_changes)(net_t *net, uint_t nowait);
    int_t  (*process_events)(net_t *net, uint_t flags);

    int_t  (*init)(net_t *net,int_t events);
    void       (*done)(net_t *net);
} event_actions_t;

extern event_actions_t   event_actions;




/*
 * The event filter is deleted after a notification without an additional
 * syscall: kqueue, epoll.
 */
#define USE_ONESHOT_EVENT    0x00000002

/*
 * The event filter notifies only the changes and an initial level:
 * kqueue, epoll.
 */
#define USE_CLEAR_EVENT      0x00000004


/*
 * The event filter requires to do i/o operation until EAGAIN: epoll, rtsig.
 */
#define USE_GREEDY_EVENT     0x00000020

/*
 * The event filter is epoll.
 */
#define USE_EPOLL_EVENT      0x00000040

/*
 * The event filter is deleted just before the closing file.
 * Has no meaning for select and poll.
 * kqueue, epoll, rtsig, eventport:  allows to avoid explicit delete,
 *                                   because filter automatically is deleted
 *                                   on file close,
 *
 * /dev/poll:                        we need to flush POLLREMOVE event
 *                                   before closing file.
 */
#define CLOSE_EVENT    1

/*
 * disable temporarily event filter, this may avoid locks
 * in kernel malloc()/free(): kqueue.
 */
#define DISABLE_EVENT  2

/*
 * event must be passed to kernel right now, do not wait until batch processing.
 */
#define FLUSH_EVENT    4


/* these flags have a meaning only for kqueue */
#define LOWAT_EVENT    0
#define VNODE_EVENT    0




#define READ_EVENT     EPOLLIN
#define WRITE_EVENT    EPOLLOUT

#define LEVEL_EVENT    0
#define CLEAR_EVENT    EPOLLET
#define ONESHOT_EVENT  0x70000000


#ifndef CLEAR_EVENT
#define CLEAR_EVENT    0    /* dummy declaration */
#endif


#define process_changes  event_actions.process_changes
#define process_events   event_actions.process_events
#define done_events      event_actions.done

#define add_event        event_actions.add
#define del_event        event_actions.del
#define add_conn         event_actions.add_conn
#define del_conn         event_actions.del_conn



#define EVENT_MODULE      0x544E5645  /* "EVNT" */
#define EVENT_CONF        0x02000000


// extern uint_t             accept_events;
// extern uint_t             accept_mutex_held;
// extern msec_t             accept_mutex_delay;
// extern int_t              accept_disabled;






extern uint_t             event_flags;
extern module_t           events_module;
extern module_t           event_core_module;

void event_accept(event_t *ev);

void process_events_and_timers(net_t *net);
int_t handle_read_event(event_t *rev, uint_t flags);
int_t handle_write_event(event_t *wev, size_t lowat);


#define nonblocking(s)  fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)
#define nonblocking_n   "fcntl(O_NONBLOCK)"

#define blocking(s)     fcntl(s, F_SETFL, fcntl(s, F_GETFL) & ~O_NONBLOCK)
#define blocking_n      "fcntl(!O_NONBLOCK)"

#endif /* _EVENT_H_INCLUDED_ */
