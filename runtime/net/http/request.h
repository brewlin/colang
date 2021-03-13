#ifndef _REQUEST_H_
#define _REQUEST_H_
#include "config.h"
#include "stringutils.h"


// HTTP请求的方法
typedef enum {
    HTTP_METHOD_UNKNOWN = -1,
    HTTP_METHOD_NOT_SUPPORTED = 0,
    HTTP_METHOD_GET = 1,
    HTTP_METHOD_HEAD = 2
} http_method;

// HTTP协议版本
typedef enum {
    HTTP_VERSION_UNKNOWN,
    HTTP_VERSION_09,
    HTTP_VERSION_10,
    HTTP_VERSION_11
} http_version;

// HTTP头部中使用的键值对
typedef struct {
    string *key;
    string *value;
} keyvalue;

// HTTP头部，包含若干个键值对，键值对的数量和头部长度
typedef struct {
    keyvalue *ptr;
    size_t len;
    size_t size;
} http_headers;

// HTTP请求结构体，包含HTTP方法，版本，URI，HTTP头，内容长度
typedef struct {
    http_method method;
    http_version version;
    char *method_raw;
    char *version_raw;
    char *uri;
    http_headers *headers;
    int content_length;
} http_request;

// HTTP响应结构体，包含内容长度，内容，HTTP头部
typedef struct {
    int content_length;
    string *entity_body;
    http_headers *headers;
} http_response;


typedef enum {
    HTTP_RECV_STATE_WORD1,
    HTTP_RECV_STATE_WORD2,
    HTTP_RECV_STATE_WORD3,
    HTTP_RECV_STATE_SP1,
    HTTP_RECV_STATE_SP2,
    HTTP_RECV_STATE_LF,
    HTTP_RECV_STATE_LINE
} http_recv_state;

// 客户端连接结构体
struct http_connection_s{
    // 客户端连接的socket
    // int sockfd;
    connection_t *connection;
    // 状态码
    int status_code;
    // 接收队列
    string *recv_buf;
    // HTTP请求
    http_request *request;
    // HTTP响应
    http_response *response;
    // 接收状态
    http_recv_state recv_state;
    // 客户端地址信息
    struct sockaddr_in *addr;
    // 请求长度
    size_t request_len;
    // 请求文件的真实路径
    char real_path[PATH_MAX];
    log_t *log;
};


// 初始化HTTP请求
http_request* http_request_init();

// 根据HTTP/1.0协议验证HTTP请求是否合法
int http_request_complete(http_connection *con);

// 解析HTTP请求
void http_request_parse(http_connection *con);

// 接受客户端连接
void connection_init(http_connection *con);


// 处理客户端连接
// int connection_handler(http_connection *con);
void connection_handler(event_t *ev);


#endif
