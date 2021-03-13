#include "config.h"
#include "stringutils.h"
#include "log.h"
#include "request.h"
#include "connection.h"

static void clean(void *data)
{
    log_info(NET->log,"log: clean the log fd");
    log_t  *l = (log_t*)data;
    if (l->logfp)
        fclose(l->logfp);
    closelog();
}
// 以append模式打开日志文件
void log_open(log_t *log, const char *logfile) {
    if (log->use_logfile) {
        log->logfp = fopen(logfile, "a");

        if (!log->logfp) {
            perror(logfile);
            exit(1);
        }
        //auto clean the file 
        return;
    }

    openlog("weblog_t", LOG_NDELAY | LOG_PID, LOG_DAEMON);
}

// 生成时间戳字符串
static void date_str(string *s) {
    struct tm *ti;
    time_t rawtime;
    char local_date[100];
    char zone_str[20];
    int zone;
    char zone_sign;

    time(&rawtime);
    ti = localtime(&rawtime);
    zone = ti->tm_gmtoff / 60;

    if (ti->tm_zone < 0) {
        zone_sign = '-';
        zone = -zone;
    } else
        zone_sign = '+';
    
    zone = (zone / 60) * 100 + zone % 60;

    strftime(local_date, sizeof(local_date), "%d/%b/%Y:%X", ti);
    snprintf(zone_str, sizeof(zone_str), " %c%.4d", zone_sign, zone);

    string_append(s, local_date);
    string_append(s, zone_str);
}

// 记录HTTP请求
void log_request(http_connection *con) {
    connection_t *sock = con->connection;
    log_t *log = sock->log;
    http_request *req = con->request;
    http_response *resp = con->response;
    char host_ip[INET_ADDRSTRLEN];
    char content_len[20];
    string *date = string_init();

//    if (!con)
//        return;

    if (resp->content_length > -1 && req->method != HTTP_METHOD_HEAD) {
        snprintf(content_len, sizeof(content_len), "%d", resp->content_length); 
    } else {
        strcpy(content_len, "-");
    }
    inet_ntop(con->addr->sin_family, &con->addr->sin_addr, host_ip, INET_ADDRSTRLEN);
    date_str(date);

    // 日志中需要记录的项目：IP，时间，访问方法，URI，版本，状态，内容长度
    if (log->use_logfile) {
        fprintf(log->logfp, "%s - - [%s] \"%s %s %s\" %d %s\n",
                host_ip, date->ptr, req->method_raw, req->uri,
                req->version_raw, con->status_code, content_len);
        fflush(log->logfp);
    } else {
        syslog(LOG_ERR, "%s - - [%s] \"%s %s %s\" %d %s",
                host_ip, date->ptr, req->method_raw, req->uri,
                req->version_raw, con->status_code, content_len);
    }

}

// 写入日志函数
static void log_write(log_t *log, const char *type, const char *format, va_list ap) {
    string *output = string_init(NULL);

    // 写入时间，消息类型
    if (log->use_logfile) {
        string_append_ch(output, '[');
        date_str(output);
        string_append(output, "] ");
    }

    string_append(output, "[");
    string_append(output, type);
    string_append(output, "] ");
    
    string_append(output, format);

    if (log->use_logfile) {
        string_append_ch(output, '\n');
        vfprintf(log->logfp, output->ptr, ap);
        fflush(log->logfp);
    } else {
        vsyslog(LOG_ERR, output->ptr, ap);
    }

    string_free(output);
}

// 记录出错信息
void log_error(log_t *log, const char *format, ...) {
    va_list ap;

    va_start(ap, format);
    log_write(log, "error", format, ap);
    va_end(ap);
}

// 记录日志信息
void log_info(log_t *log, const char *format, ...) {
    va_list ap;

    va_start(ap, format);
    log_write(log, "info", format, ap);
    va_end(ap);
}
