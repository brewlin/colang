#include <stdio.h>
#include "CoreValue.h"

/**
 * lhs  rhs 都是堆变量
 * @param opt
 * @param lhs
 * @param rhs
 */
CoreValue* binaryOper(int opt, CoreValue *lhs, CoreValue* rhs)
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
//            return *lhs == rhs;
        case TK_NE:
//            return *lhs != rhs;
        default:
            return NULL;
    }
}