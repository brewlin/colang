#include "http.h"
#include "connection.h"
#include "net.h"
#include "request.h"
#include "event.h"
#include "log.h"

static int_t  http_process_init(net_t * net);
static listening_t *http_add_listening(net_t *net, http_listen_opt_t *opt);
static void http_init_request(event_t *rev);
static void http_init_connection(connection_t *c);
static void http_empty_handler(event_t *wev);
void http_close_connection(connection_t *c);

module_t  http_core_module = {
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    http_process_init,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
};
//注册一个http监听事件
Value* register_http(int port,net_t* net){
    log_info(net->log,"http: register http server");
    http_listen_opt_t   lsopt;
    struct sockaddr_in serv_addr;
    memzero(&lsopt, sizeof(http_listen_opt_t));
    memzero(&serv_addr,sizeof(serv_addr));
    // listen 127.0.0.1:8000;
    // listen 127.0.0.1 不加端口，默认监听80端口;
    // listen 8000
    // listen *:8000
    // listen localhost:8000

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    //TODO:检查port重复注册

    lsopt.sockaddr = (struct sockaddr *)&serv_addr;
    lsopt.socklen = sizeof(serv_addr);

    lsopt.backlog = BACKLOG;
    lsopt.rcvbuf = -1;
    lsopt.sndbuf = -1;

    listening_t           *ls;
    ls = http_add_listening(net, &lsopt);

    Value* ret = gc_malloc(sizeof(Value));
    ret->type  = Int;
    ret->data  = OK;
    if (ls == NULL) {
        ret->data = ERROR;
    }
    return ret;
}
//这里其实应该是核心http模块的启动，主要是启动监听端口
//但是端口配置添加 listening_t 在nginx中是通过nginx.conf配置解析时添加的
//我们这里作为演示就直接放到http core模块启动方法中
static int_t http_process_init(net_t *net)
{
    log_info(net->log,"http: process init");
    //初始化对应socket
    return open_listening_sockets(net);
}


static listening_t *http_add_listening(net_t *net, http_listen_opt_t *opt)
{
    listening_t           *ls;

    ls = create_listening(net, opt->sockaddr, opt->socklen);
    if (ls == NULL) {
        return NULL;
    }

    ls->handler = http_init_connection;

    ls->backlog = opt->backlog;
    ls->rcvbuf = opt->rcvbuf;
    ls->sndbuf = opt->sndbuf;
    ls->root = "/tmp/www";


    return ls;
}

static void http_init_connection(connection_t *c)
{
    event_t         *rev;
    rev = c->read;
    rev->handler = http_init_request;
    c->write->handler = http_empty_handler;

    if (rev->ready) {
        rev->handler(rev);
        return;
    }

    if (handle_read_event(rev, 0) != OK) {
        http_close_connection(c);
        return;
    }
}


static void http_init_request(event_t *rev)
{
    connection_t           *c;
    http_connection         *hc;
    c = rev->data;
    hc = c->data;
    if (hc == NULL) {
        hc = gc_malloc(sizeof(http_connection));
        if (hc == NULL) {
            http_close_connection(c);
            return;
        }
    }
    c->data = hc;
    hc->connection = c;
    hc->log = c->log;

    connection_init(hc);
    rev->handler = connection_handler;
    // connection_handler(hc);
    // connection_close(hc);

    // http_close_connection(c);
    rev->handler(rev);
}


void http_empty_handler(event_t *wev)
{
    log_info(wev->log,"http empty handler");

    return;
}
 
/**
 * 关闭释放连接
 */ 
void http_close_connection(connection_t *c)
{

    log_error(c->log,"close http connection: %d", c->fd);
    c->destroyed = 1;
    close_connection(c);
}