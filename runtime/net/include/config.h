#ifndef __CONFIG_H_INCLUDE_
#define __CONFIG_H_INCLUDE_

#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define __USE_GNU
#include <sys/socket.h>

#include <string.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <netdb.h>
#include <limits.h>
#include <sys/stat.h>
#include <stddef.h>

#include <arpa/inet.h>
#include <syslog.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <assert.h>
#include <ctype.h>

#define OK                 0
#define ERROR              -1
#define AGAIN              -2
#define UPDATE_TIME         1
#define POST_EVENTS         2
#define POST_THREAD_EVENTS  4

#define memzero(buf, n)             (void) memset(buf, 0, n)
#define SOCKADDRLEN                 sizeof(struct sockaddr)
#define close_socket                close
#define socket_errno                errno
#define msleep(ms)                  usleep(ms * 1000)

typedef intptr_t        int_t;
typedef uintptr_t       uint_t;
typedef int             err_t;
typedef unsigned char   u_char;

typedef struct net_s              net_t;
typedef struct event_s              event_t;
typedef struct connection_s         connection_t;
typedef struct http_connection_s    http_connection;
typedef struct listening_s          listening_t;
typedef struct module_s             module_t;
typedef struct http_request_s       http_request_t;
typedef struct log_s                log_t;

typedef struct {
    size_t      len;
    u_char     *data;
} str_t;

extern net_t *NET;
#endif
