/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Value.h"
#include "String.h"
Value* value_plus(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
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
Value* value_equal(Value* lhs,Value* rhs) {
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    result->data = 0;
    // 如果有string则直接进行string比较
    if(lhs->type == String || rhs->type == String){
        result->data = value_string_equal(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->data = value_int_equal(lhs,rhs);
    }
    return result;
}
Value* value_notequal(Value* lhs,Value* rhs)
{
    Value* result = (Value*)gc_malloc(sizeof(Value));
    result->type = Bool;
    //默认为true  不等于
    result->data = 1;
    // 如果有string则直接进行string比较
    if(lhs->type == String || rhs->type == String){
        result->data = value_string_notequal(lhs,rhs);
        return result;
    }
    //有int类型就进行int类型相加
    if (lhs->type == Int || rhs->type == Int){
        result->data = value_int_notequal(lhs,rhs);
    }
    return result;
}

int isTrue(Value* cond){
    switch (cond->type){
        case Int:
            return cond->data > 0;
        case Double:
            return cond->data > 0;
        case String:
            return cond->data != NULL;
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
 * lhs  rhs 都是堆变量
 * @param opt
 * @param lhs
 * @param rhs
 */
Value* binaryOper(int opt, Value *lhs, Value* rhs)
{
    if( !lhs || !rhs ){
        return NULL;
    }
    switch (opt){
        case TK_ASSIGN:
            return rhs;
        case TK_PLUS:
            return value_plus(lhs,rhs);
        case TK_MINUS:
//            return *lhs - rhs;
        case TK_MUL:
//            return *lhs * rhs;
        case TK_DIV:
//            return *lhs / rhs;
        case TK_BITAND:
//            return *lhs & rhs;
        case TK_BITOR:
//            return *lhs | rhs;

        case TK_LT:
//            return *lhs < rhs;
        case TK_LE:
//            return *lhs <= rhs;
        case TK_GE:
//            return *lhs >= rhs;
        case TK_GT:
//            return *lhs > rhs;
        case TK_EQ:
            return value_equal(lhs,rhs);
//            return *lhs == rhs;
        case TK_NE:
//            return *lhs != rhs;
            return value_notequal(lhs,rhs);
        default:
            return NULL;
    }
}