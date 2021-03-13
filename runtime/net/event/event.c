#include "event.h"
#include "net.h"
#include "log.h"

#define DEFAULT_CONNECTIONS  512

static int_t event_process_init(net_t *net);

module_t event_core_module = {
    NULL,
    NULL,
    event_process_init,
    NULL,NULL,NULL,NULL
};

uint_t            event_flags;
extern event_actions_t   event_actions;


uint_t            accept_events;
int_t             accept_disabled;

int_t
handle_read_event(event_t *rev, uint_t flags)
{
    log_info(NET->log,"event: handle_read_event");
    if (event_flags & USE_CLEAR_EVENT) {

        if (!rev->active && !rev->ready) {
            if (add_event(rev, READ_EVENT, CLEAR_EVENT)
                == ERROR)
            {
                return ERROR;
            }
        }
        return OK;

    }
    return OK;
}


int_t
handle_write_event(event_t *wev, size_t lowat)
{
    connection_t  *c = (connection_t*)wev->data;
    log_info(c->log,"event: handle write event");

    if (event_flags & USE_CLEAR_EVENT) {

        /* kqueue, epoll */

        if (!wev->active && !wev->ready) {
            if (add_event(wev, WRITE_EVENT,
                              CLEAR_EVENT | (lowat ? LOWAT_EVENT : 0))
                == ERROR)
            {
                return ERROR;
            }
        }

        return OK;

    } 


    return OK;
}




static int_t
event_process_init(net_t *net)
{
    log_info(net->log,"event: event_process_init");
    uint_t           i;
    event_t         *rev, *wev;
    listening_t     *ls;
    connection_t    *c, *next;
    net->connection_n = 100;

    //init epoll_create epoll_events
    event_actions.init(net,net->connection_n/2);

    //allocate connection pool
    net->connections = (connection_t *)gc_malloc(sizeof(connection_t) * net->connection_n);
    if (net->connections == NULL) {
        return ERROR;
    }

    c = net->connections;

    //allocate read events pool
    net->read_events = gc_malloc(sizeof(event_t) * net->connection_n);
    if (net->read_events == NULL) {
        return ERROR;
    }

    rev = net->read_events;
    for (i = 0; i < net->connection_n; i++) {
        rev[i].log = net->log;
        rev[i].closed = 1;
        rev[i].instance = 1;
    }
    //allocate write events pool
    net->write_events = (event_t *)gc_malloc(sizeof(event_t) * net->connection_n);
    if (net->write_events == NULL) {
        return ERROR;
    }

    wev = net->write_events;
    for (i = 0; i < net->connection_n; i++) {
        wev[i].log = net->log;
        wev[i].closed = 1;
    }

    i = net->connection_n;
    next = NULL;

    //related connection - read event - write event
    do {
        i--;
        c[i].log  = net->log;
        c[i].data = next;
        c[i].read = &net->read_events[i];
        c[i].write = &net->write_events[i];
        c[i].fd = (socket_t) -1;

        next = &c[i];

    } while (i);

    net->free_connections = next;
    net->free_connection_n = net->connection_n;

    /* for each listening socket */
    // pack the listening_t to connection
    ls = net->listening;
    while(ls != NULL)
    {
        c = get_connection(ls->fd);

        if (c == NULL) {
            return ERROR;
        }


        c->listening = ls;
        ls->connection = c;

        rev = c->read;

        rev->accept = 1;

        rev->handler = event_accept;


        if (add_event(rev, READ_EVENT, 0) == ERROR) {
            return ERROR;
         }
        ls = ls->next;

    }

    return OK;
}


