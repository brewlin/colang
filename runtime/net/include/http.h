#ifndef _HTTP_H_INCLUDED_
#define _HTTP_H_INCLUDED_

#include "config.h"


typedef struct {
    struct sockaddr           *sockaddr;
    socklen_t                  socklen;

    unsigned                   set:1;
    unsigned                   default_server:1;
    unsigned                   bind:1;
    unsigned                   wildcard:1;
    unsigned                   ssl:1;
    unsigned                   http2:1;
    unsigned                   deferred_accept:1;
    unsigned                   reuseport:1;
    unsigned                   so_keepalive:2;
    unsigned                   proxy_protocol:1;

    int                        backlog;
    int                        rcvbuf;
    int                        sndbuf;

} http_listen_opt_t;

/**
 * 关闭释放连接
 */ 
void http_close_connection(connection_t *c);

#endif /* _HTTP_H_INCLUDED_ */
