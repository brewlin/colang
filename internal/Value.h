/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_TYPE_H
#define LANG_TYPE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/Token.h"

//extern gc_malloc
#define gc_malloc malloc
#define gc_free   free

/**
 * 动态变量类型定义
 */
typedef struct core_value
{
    long type;
    void* data;
}Value;


/*********************+ - * \**************************/
Value* value_plus(Value* lhs,Value* rhs);
char*  value_string_plus(Value* lhs,Value* rhs);
long   value_int_plus(Value* lhs,Value* rhs);


Value* value_minus(Value* lhs,Value* rhs);
char*  value_string_minus(Value* lhs,Value* rhs);
long   value_int_minus(Value* lhs,Value* rhs);

Value* value_mul(Value* lhs,Value* rhs);
char*  value_string_mul(Value* lhs,Value* rhs);
long   value_int_mul(Value* lhs,Value* rhs);

Value* value_div(Value* lhs,Value* rhs);
char*  value_string_div(Value* lhs,Value* rhs);
long   value_int_div(Value* lhs,Value* rhs);

/*********************位操作**************************/
Value* value_bitand(Value* lhs,Value* rhs);
char*  value_string_bitand(Value* lhs,Value* rhs);
long   value_int_bitand(Value* lhs,Value* rhs);

Value* value_bitor(Value* lhs,Value* rhs);
char*  value_string_bitor(Value* lhs,Value* rhs);
long   value_int_bitor(Value* lhs,Value* rhs);

Value* value_shift_left(Value* lhs,Value* rhs);
char*  value_string_shift_left(Value* lhs,Value* rhs);
long   value_int_shift_left(Value* lhs,Value* rhs);

Value* value_shift_right(Value* lhs,Value* rhs);
char*  value_string_shift_right(Value* lhs,Value* rhs);
long   value_int_shift_right(Value* lhs,Value* rhs);

/*********************逻辑操作**************************/
Value* value_equal(Value* lhs,Value* rhs,int equal);
int    value_string_equal(Value* lhs,Value* rhs,int equal);
int    value_int_equal(Value* lhs,Value* rhs,int equal);

Value* value_lowerthan(Value* lhs,Value* rhs,int equal);
int    value_string_lowerthan(Value* lhs,Value* rhs,int equal);
int    value_int_lowerthan(Value* lhs,Value* rhs,int equal);

Value* value_greaterthan(Value* lhs,Value* rhs,int equal);
int    value_string_greaterthan(Value* lhs,Value* rhs,int equal);
int    value_int_greaterthan(Value* lhs,Value* rhs,int equal);

/*********************运算操作**************************/
Value* binary_operator(int opt, Value *lhs, Value* rhs);
void   unary_operator(int opt, Value *lhs, Value* rhs);

#endif //LANG_TYPE_H
