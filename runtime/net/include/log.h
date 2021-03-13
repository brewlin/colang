#ifndef _LOG_H_
#define _LOG_H_

#include "net.h"
#include "config.h"

struct log_s {
    int_t                use_logfile;
    FILE                 *logfp;
};

// 打开日志文件
void log_open(log_t *log, const char *logfile);

// 关闭日志文件
void log_close(log_t *log);

// 记录HTTP请求
void log_request(http_connection *con);

// 记录出错信息
void log_error(log_t *log, const char *format, ...);

// 记录日志信息
void log_info(log_t *log, const char *format, ...);

#endif
