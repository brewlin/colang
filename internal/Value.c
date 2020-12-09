/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Value.h"
#include "String.h"
#include "Array.h"
#include "Map.h"
/**
 * + operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_plus(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //有字符串就最终类型是字符串
    if(lhs->type == String || rhs->type == String){
        result->type = String;
        result->data = value_string_plus(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_plus(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * - operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_minus(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //有字符串就最终类型是字符串
    if(lhs->type == String || rhs->type == String){
        result->type = String;
        result->data = value_string_minus(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_minus(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * * operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_mul(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //有字符串就最终类型是字符串
    if(lhs->type == String || rhs->type == String){
        result->type = String;
        result->data = value_string_mul(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_mul(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * / operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_div(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //字符串的触发运算全部返回0
    if(lhs->type == String || rhs->type == String){
        result->type = Int;
        result->data = value_string_div(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_div(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * & operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_bitand(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //字符串的触发运算全部返回0
    if(lhs->type == String || rhs->type == String){
        result->type = Int;
        result->data = value_string_bitand(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_bitand(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * | operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_bitor(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //字符串的触发运算全部返回0
    if(lhs->type == String || rhs->type == String){
        result->type = Int;
        result->data = value_string_bitor(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_bitor(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * << operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_shift_left(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //字符串的触发运算全部返回0
    if(lhs->type == String || rhs->type == String){
        result->type = Int;
        result->data = value_string_shift_left(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_shift_left(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * >> operator
 * @param lhs
 * @param rhs
 * @return
 */
Value* value_shift_right(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    if(!lhs){
        memcpy(result,rhs, sizeof(Value));
        return result;
    }
    //字符串的触发运算全部返回0
    if(lhs->type == String || rhs->type == String){
        result->type = Int;
        result->data = value_string_shift_right(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->type = Int;
        result->data = value_int_shift_right(lhs,rhs);
        return result;
    }
    exit(1);
}
/**
 * == operator
 * @param lhs
 * @param rhs
 * @return Value*
 */
Value* value_equal(Value* lhs,Value* rhs,int equal) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    result->data = 0;
    // 如果有string则直接进行string比较
    if(lhs->type == String || rhs->type == String){
        result->data = value_string_equal(lhs,rhs,equal);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->data = value_int_equal(lhs,rhs,equal);
    }
    return result;
}
/**
 * < operator
 * @param lhs
 * @param rhs
 * @return Value*
 */
Value* value_lowerthan(Value* lhs,Value* rhs,int equal)
{
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    //默认为true  小于
    result->data = 1;
    // 如果有string则直接进行string比较
    if(lhs->type == String || rhs->type == String){
        result->data = value_string_lowerthan(lhs,rhs,equal);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->data = value_int_lowerthan(lhs,rhs,equal);
    }
    return result;
}
/**
 * > operator
 * @param lhs
 * @param rhs
 * @return Value*
 */
Value* value_greaterthan(Value* lhs,Value* rhs,int equal)
{
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    //默认为true  大于
    result->data = 1;
    // 如果有string则直接进行string比较
    if(lhs->type == String || rhs->type == String){
        result->data = value_string_greaterthan(lhs,rhs,equal);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->data = value_int_greaterthan(lhs,rhs,equal);
    }
    return result;
}

/**
 * && operator
 * @param lhs
 * @param rhs
 * @return Value*
 */
Value* value_logand(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    result->data = isTrue(lhs) && isTrue(rhs);
    return result;
}
Value* value_logor(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    result->data = isTrue(lhs) || isTrue(rhs);
    return result;
}

/**
 *
 * @param root
 * @param index
 * @param var
 */
void   kv_update(Value* root,Value* index,Value* var)
{
    if(root->type == Array){
        return arr_updateone(root,index,var);
    }
    if(root->type == Map){
        return map_insert(root,index,var);
    }
    printf("[kv_update] arr or map is invalid ,probably something wrong\n");
}
/**
 *
 * @param root
 * @param index
 * @return
 */
Value* kv_get(Value* root,Value* index){
    if(root->type == Array){
        return arr_get(root,index);
    }
    if(root->type == Map){
        return map_find(root,index);
    }
    printf("[kv_get] arr or map is invalid ,probably something wrong\n");
}
/**
 * tell if itstrue
 * @param cond
 * @return bool
 */
int isTrue(Value* cond){
    switch (cond->type){
        case Int:
            return cond->data > 0;
        case Double:
            return cond->data > 0;
        case String:
            return stringlen(cond->data);
        case Bool:
            return cond->data;
        case Char:
            return cond->data != 0;
        case Null:
            return 0;
        default:
            return 0;
    }
}
/**
 *
 * @param opt
 * @param lhs
 * @param rhs
 */
Value* unary_operator_switch(int opt,Value* lhs,Value* rhs){
    Value* ret;
    switch (opt){
        case TK_ASSIGN:
            ret = rhs;break;
        case TK_PLUS_AGN:
            ret = value_plus(lhs,rhs);break;
        case TK_MINUS_AGN:
            ret = value_minus(lhs,rhs);break;
        case TK_MUL_AGN:
            ret = value_mul(lhs,rhs);break;
        case TK_DIV_AGN:
            ret = value_div(lhs,rhs);break;
        case TK_BITAND_AGN:
            ret = value_bitand(lhs,rhs);break;
        case TK_BITOR_AGN:
            ret = value_bitor(lhs,rhs);break;
        case TK_SHIFTL_AGN:
            ret = value_shift_left(lhs,rhs);break;
        case TK_SHIFTR_AGN:
            ret = value_shift_right(lhs,rhs);break;
        default:
            printf(" [unary-op] unkown op:%d\n",opt);
            ret = rhs;
    }
    return ret;
}
/**
 *
 * @param opt
 * @param lhs
 * @param rhs
 * @return
 */
void unary_operator(int opt,Value *lhs,Value* rhs)
{
    if( !lhs || !rhs ){
        printf(" [unary-op] probably wrong at there! lhs:%p rhs:%p\n",lhs,rhs);
        return;
    }
    Value* ret = unary_operator_switch(opt,*(Value**)lhs,rhs);
    // assign =
    *(Value**)lhs = ret;
}
/**
 * lhs  rhs 都是堆变量
 * @param opt
 * @param lhs
 * @param rhs
 */
Value* binary_operator(int opt, Value *lhs, Value* rhs)
{
    if( !lhs || !rhs ){
        printf(" [binary-op] probably wrong at there! lhs:%p rhs:%p\n",lhs,rhs);
        return NULL;
    }
    Value* ret;
    switch (opt){
        case TK_PLUS:// +
            ret =  value_plus(lhs,rhs);break;
        case TK_MINUS:// -
            ret = value_minus(lhs,rhs);break;
        case TK_MUL:// *
            ret =  value_mul(lhs,rhs);break;
        case TK_DIV:// \ .
            ret =  value_div(lhs,rhs);break;

        case TK_BITAND:// &
            ret =  value_bitand(lhs,rhs);break;
        case TK_BITOR:// |
            ret =  value_bitor(lhs,rhs);break;
        case TK_SHIFTL:
            ret =  value_shift_left(lhs,rhs);break;
        case TK_SHIFTR:
            ret =  value_shift_right(lhs,rhs);break;

        case TK_LT:// <
            ret =  value_lowerthan(lhs,rhs,FALSE);break;
        case TK_LE:// <=
            ret =  value_lowerthan(lhs,rhs,TRUE);break;
        case TK_GE:// >=
            ret =  value_greaterthan(lhs,rhs,TRUE);break;
        case TK_GT:// >
            ret =  value_greaterthan(lhs,rhs,FALSE);break;
        case TK_EQ:// ==
            ret =  value_equal(lhs,rhs,TRUE);break;
        case TK_NE:// !=
            ret =  value_equal(lhs,rhs,FALSE);break;
        case TK_LOGAND:// &&
            ret =  value_logand(lhs,rhs);break;
        case TK_LOGOR:// ||
            ret =  value_logor(lhs,rhs);break;
        default:
            printf(" [binary-op] unknow op:%d \n",opt);
            return NULL;
    }
    if((ret->data == 1 && ret->type == String) || ret == 0x7ffff7fad090){
        printf("some erro");
    }
    return ret;
}