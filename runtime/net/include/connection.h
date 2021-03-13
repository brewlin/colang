#ifndef _CONNECTION_H_INCLUDED_
#define _CONNECTION_H_INCLUDED_


#include "config.h"
#include "net.h"

#define BACKLOG 10


typedef void (*event_handler_pt)(event_t *ev);
typedef void (*connection_handler_pt)(connection_t *c);

typedef ssize_t (*recv_pt)(connection_t *c, u_char *buf, size_t size);
typedef ssize_t (*send_pt)(connection_t *c, u_char *buf, size_t size);

typedef int  socket_t;


struct listening_s {
    //将多个socket连接成链表
    listening_t*    next;
    //socket 连接句柄
    socket_t        fd;
    //监听socketaddr 地址
    struct sockaddr    *sockaddr;
    //sockadd 地址长度
    socklen_t           socklen;    /* size of sockaddr */

    //套接字类型  sock_stream 表示tcp
    int                 type;
    //表示待处理的连接 可以等待的最大队列书
    int                 backlog;
    //内核套接字接收缓冲区大小
    int                 rcvbuf;
    //内核套接字发送缓冲区大小
    int                 sndbuf;

    //web文件目录
    char                *root;

    /* handler of accepted connection */
    //当新的连接成功后的处理方法
    connection_handler_pt   handler;

    /* should be here because of the AcceptEx() preread */
    size_t              post_accept_buffer_size;
    /* should be here because of the deferred accept */
    //当建立连接后 post_accept_timeout 秒后还是没有收到用户数据，则丢弃该连接
    // msec_t          post_accept_timeout;
    //前一个 节点  由郭哥listening_t 节点组成单链表
    listening_t    *previous;
    //当前监听句柄对应着connection_t 结构体
    connection_t   *connection;
    //1 跳过 设置当前结构体中的套接字  0 正常初始化
    unsigned            ignore:1;
    //1 表示该套接字已监听
    unsigned            listen:1;

};


typedef enum {
     ERROR_ALERT = 0,
     ERROR_ERR,
     ERROR_INFO,
     ERROR_IGNORE_ECONNRESET,
     ERROR_IGNORE_EINVAL
} connection_log_error_e;


typedef enum {
     TCP_NODELAY_UNSET = 0,
     TCP_NODELAY_SET,
     TCP_NODELAY_DISABLED
} connection_tcp_nodelay_e;


typedef enum {
     TCP_NOPUSH_UNSET = 0,
     TCP_NOPUSH_SET,
     TCP_NOPUSH_DISABLED
} connection_tcp_nopush_e;


#define LOWLEVEL_BUFFERED  0x0f
#define SSL_BUFFERED       0x01


struct connection_s {
    void               *data;
    event_t        *read;
    event_t        *write;

    socket_t        fd;

    recv_pt         recv;
    send_pt         send;

    listening_t    *listening;
    log_t          *log;

    off_t               sent;


    struct sockaddr    *sockaddr;
    socklen_t           socklen;

    struct sockaddr    *local_sockaddr;

    unsigned            log_error:3;     /* connection_log_error_e */

    unsigned            timedout:1;
    unsigned            error:1;
    unsigned            destroyed:1;

    unsigned            idle:1;
    unsigned            reusable:1;
    unsigned            close:1;
    unsigned            sndlowat:1;

    unsigned            tcp_nodelay:2;   /* connection_tcp_nodelay_e */
    unsigned            tcp_nopush:2;    /* connection_tcp_nopush_e */


};


listening_t *create_listening(net_t *net, void *sockaddr, socklen_t socklen);
int_t set_inherited_sockets(net_t *net);
int_t open_listening_sockets(net_t *net);
void close_listening_sockets(net_t *net);
void close_connection(connection_t *c);

connection_t *get_connection(socket_t s);
void free_connection(connection_t *c);

void reusable_connection(connection_t *c, uint_t reusable);

#endif /* _CONNECTION_H_INCLUDED_ */
