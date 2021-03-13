#include "config.h"
#include "log.h"
#include "http_header.h"
#include "response.h"
#include "connection.h"

// 文件扩展名与MimeType数据结构
typedef struct {
    // 文件扩展名
    const char *ext;
    // Mime类型名
    const char *mime;
} mime;

// 目前支持的MimeType
static mime mime_types[] = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".jpg", "image/jpg"},
    {".png", "image/png"}
};

// 出错页面
static char err_file[PATH_MAX];
static const char *default_err_msg = "<HTML><HEAD><TITLE>Error</TITLE></HEAD>"
                                      "<BODY><H1>Something went wrong</H1>"
                                      "</BODY></HTML>";

// 初始化HTTP响应
http_response* http_response_init() {
    http_response *resp;
    resp = gc_malloc(sizeof(*resp));
    memset(resp, 0, sizeof(*resp));

    resp->headers = http_headers_init();
    resp->entity_body = string_init();
    resp->content_length = -1;

    return resp;
}

// 根据状态码构建响应结构中的状态消息
static const char* reason_phrase(int status_code) {
    switch (status_code) {
        case 200:
            return "OK";
        case 400:
            return "Bad Request";
        case 403:
            return "Forbidden";
        case 404:
            return "Not Found";
        case 500:
            return "Internal net_t Error";
        case 501:
            return "Not Implemented";

    }

    return "";
}

/*
 * 将响应消息发送给客户端
 */
static int send_all(http_connection *con, string *buf) {
    connection_t *sock = con->connection;
    int bytes_sent = 0;
    int bytes_left = buf->len;
    int nbytes = 0;

    while (bytes_sent < bytes_left) {
        nbytes = sock->send(sock,(u_char*)(buf->ptr+bytes_sent),bytes_left);
        // nbytes = send(con->sockfd, buf->ptr + bytes_sent, bytes_left, 0);
        
        if (nbytes == -1)
            break;

        bytes_sent += nbytes;
        bytes_left -= nbytes;
        
    }

    return nbytes != -1 ? bytes_sent : -1;
}

// 根据文件路径获得MimeType
static const char* get_mime_type(const char *path, const char *default_mime) {
    size_t path_len = strlen(path);

    for (size_t i = 0; i < sizeof(mime_types); i++) {
        size_t ext_len = strlen(mime_types[i].ext);
        const char *path_ext = path + path_len - ext_len;

        if (ext_len <= path_len && strcmp(path_ext, mime_types[i].ext) == 0)
            return mime_types[i].mime;
    
    }

    return default_mime;
}

// 检查文件权限是否可以访问
static int check_file_attrs(http_connection *con, const char *path) {
    struct stat s;

    con->response->content_length = -1;

    if (stat(path, &s) == -1) {
        con->status_code = 404;
        return -1;
    }

    if (!S_ISREG(s.st_mode)) {
        con->status_code = 403;
        return -1;
    }

    con->response->content_length = s.st_size;

    return 0;
}

// 读取文件
static int read_file(string *buf, const char *path) {
    FILE *fp;
    int fsize;

    fp = fopen(path, "r");

    if (!fp) {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    string_extend(buf, fsize + 1);
    if (fread(buf->ptr, fsize, 1, fp) > 0) {
        buf->len += fsize;
        buf->ptr[buf->len] = '\0';
    }
    
    fclose(fp);

    return fsize;
}

// 读取标准错误页面
static int read_err_file(http_connection *con, string *buf) {
    snprintf(err_file, sizeof(err_file), "%s/%d.html", con->connection->listening->root,con->status_code);
    log_info(con->log,"read_err_file: %s",err_file);

    int len = read_file(buf, err_file);

    //E 如果文件不存在则使用默认的出错信息字符串替代
    if (len <= 0) {
        string_append(buf, default_err_msg);
        len = buf->len;
    }

    return len;
}

// 构建并发送响应
static void build_and_send_response(http_connection *con) {
    
    // 构建发送的字符串
    string *buf = string_init();
    http_response *resp = con->response;

    string_append(buf, "HTTP/1.0 ");
    string_append_int(buf, con->status_code);
    string_append_ch(buf, ' ');
    string_append(buf, reason_phrase(con->status_code));
    string_append(buf, "\r\n");

    for (size_t i = 0; i < resp->headers->len; i++) {
        string_append_string(buf, resp->headers->ptr[i].key); 
        string_append(buf, ": ");
        string_append_string(buf, resp->headers->ptr[i].value);
        string_append(buf, "\r\n");
    }

    string_append(buf, "\r\n");

    if (resp->content_length > 0 && con->request->method != HTTP_METHOD_HEAD) {
        string_append_string(buf, resp->entity_body);
    }

    // 将字符串缓存发送到客户端
    send_all(con, buf);
}

/*
 * 当出错时发送标准错误页面，页面名称类似404.html
 * 如果错误页面不存在则发送标准的错误消息
 */
static void send_err_response(http_connection *con) {
    connection_t *sock = con->connection;
    http_response *resp = con->response;
    snprintf(err_file, sizeof(err_file), "%s/%d.html",sock->listening->root,con->status_code);

    // 检查错误页面
    if (check_file_attrs(con, err_file) == -1) {
        resp->content_length = strlen(default_err_msg);
        log_error(con->log, "failed to open file %s", err_file);
    }

    // 构建消息头部
    http_headers_add(resp->headers, "Content-Type", "text/html");
    http_headers_add_int(resp->headers, "Content-Length", resp->content_length);

    if (con->request->method != HTTP_METHOD_HEAD) {
       read_err_file(con, resp->entity_body); 
    }

    build_and_send_response(con);
}

/*
 * 构建响应消息和消息头部并发送消息
 * 如果请求的资源无法打开则发送错误消息
 */
static void send_response(http_connection *con) {
    http_response *resp = con->response;
    http_request *req = con->request;
    
    http_headers_add(resp->headers, "server", "ngx_server");

    if (con->status_code != 200) {
        send_err_response(con);
        return;
    }

    if (check_file_attrs(con, con->real_path) == -1) {
        send_err_response(con);
        return;
    }

    if (req->method != HTTP_METHOD_HEAD) {
        read_file(resp->entity_body, con->real_path);
    }

    // 构建消息头部
    const char *mime = get_mime_type(con->real_path, "text/plain");
    http_headers_add(resp->headers, "Content-Type", mime);
    http_headers_add_int(resp->headers, "Content-Length", resp->content_length);

    build_and_send_response(con);
}

/*
 * HTTP_VERSION_09时，只发送响应消息内容，不包含头部
 */
static void send_http09_response(http_connection *con) {
    http_response *resp = con->response;

    if (con->status_code == 200 && check_file_attrs(con, con->real_path) == 0) {
        read_file(resp->entity_body, con->real_path);
    } else {
        read_err_file(con, resp->entity_body);
    }

    send_all(con, resp->entity_body);
}

// 发送HTTP响应
void http_response_send(http_connection *con) {
    if (con->request->version == HTTP_VERSION_09) {
        send_http09_response(con);
    } else {
        send_response(con);
    }
}
