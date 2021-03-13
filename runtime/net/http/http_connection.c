#include "config.h"
#include "log.h"
#include "request.h"
#include "response.h"
#include "stringutils.h"
#include "connection.h"
#include "event.h"
#include "http.h"

/*
 * 等待并接受新的连接
 */
void connection_init(http_connection *con) {
    connection_t *sock = con->connection;

    // 初始化连接结构
    con->status_code = 0;
    con->request_len = 0;
    con->real_path[0] = '\0';

    con->recv_state = HTTP_RECV_STATE_WORD1;
    con->request = http_request_init();
    con->response = http_response_init();
    con->recv_buf = string_init();
    con->addr = (struct sockaddr_in *)sock->sockaddr;
}

/*
 * HTTP请求处理函数
 * - 从socket中读取数据并解析HTTP请求
 * - 解析请求
 * - 发送响应
 * - 记录请求日志
 */
// int connection_handler(http_connection *con) {
void connection_handler(event_t *ev) {
    connection_t *sock = (connection_t *)ev->data;
    http_connection *con = sock->data;
    char buf[512];
    int nbytes;


    while ((nbytes =  sock->recv(sock,(u_char*)buf,sizeof(buf))) > 0) {
        string_append_len(con->recv_buf, buf, nbytes);

        if (http_request_complete(con) != 0)
            break;
    }

    if (nbytes <= 0) {
        if (nbytes == 0) {
            log_info(con->log, "socket %d closed", sock->fd);
            http_close_connection(sock);
            return;
        
        } else if (nbytes == AGAIN) {
            if (handle_read_event(ev, 0) != OK) {
                http_close_connection(sock);
                return;
            }
            log_error(con->log, "read: %s", strerror(errno));
            return; 
        }
    }
    http_request_parse(con); 
    http_response_send(con);
    log_request(con);
    http_close_connection(sock);
}
