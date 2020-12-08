/**
 *@ClassName Object
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/7 0007 下午 5:54
 *@Version 1.0
 **/
#ifndef COLANG_OBJECT_H
#define COLANG_OBJECT_H

#include "Array.h"
#include "Value.h"
#include "Map.h"

rbtree_t* object_create(int size);
Value* object_member_update(Value* object,uint_t k,Value* v);
Value* object_member_get(Value* object, uint_t k);
void   object_operator(int opt,Value* object,uint_t k,Value* value);

#endif //COLANG_OBJECT_H
