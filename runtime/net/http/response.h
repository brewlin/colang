#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "config.h"

// 初始化HTTP响应
http_response* http_response_init();

// 发送HTTP响应
void http_response_send(http_connection *con);

#endif
