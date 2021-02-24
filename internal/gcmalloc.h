/**
 *@ClassName gcmalloc
 *@Deacription go
 *@Author brewlin
 *@Date 2020/11/25 0025 上午 10:49
 *@Version 1.0
 **/
#ifndef CO_LANG_GCMALLOC_H
#define CO_LANG_GCMALLOC_H

#include "Value.h"

Value* newobject(int type,void* data);
long   get_object_value(Value* obj);

#endif //CO_LANG_GCMALLOC_H
