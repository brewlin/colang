/**
 *@Author brewlin
 **/
#ifndef CO_LANG_GO_H
#define CO_LANG_GO_H

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


#define Null   0
#define Int    1
#define Double 2
#define String 3
#define Bool   4
#define Char   5
#define Array  6
#define Map    7
#define Object 8

typedef struct core_value
{
    long type;
    void* data;
}Value;

Value* newobject(int type,void* data);




#endif //CO_LANG_GO_H
