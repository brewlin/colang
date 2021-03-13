#ifndef _HTTP_HEADER_H_
#define _HTTP_HEADER_H_

#include "request.h"
#include "config.h"

// 初始化HTTP头部
http_headers* http_headers_init();

// 添加新的key-value对到HTTP头部
void http_headers_add(http_headers *h, const char *key, const char *value);
void http_headers_add_int(http_headers *h, const char *key, int value);

#endif
