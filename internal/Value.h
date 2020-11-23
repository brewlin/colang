/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_TYPE_H
#define LANG_TYPE_H
#include <stdio.h>
#include <stdlib.h>

//extern gc_malloc
#define gc_malloc malloc

#define Null   0
#define Int    1
#define Double 2
#define String 3
#define Bool   4
#define Char   5
#define Array  6
#define Map    7
#define Object 8

//TYPE TOKEN
enum Token {
    //invalid identifier eof
            INVALID = 0, TK_IDENT, TK_EOF,

    //int string double char
            LIT_INT,   LIT_STR,  LIT_DOUBLE, LIT_CHAR,

    // & | ^ ~
            TK_BITAND, TK_BITOR,TK_BITXOR,TK_BITNOT ,

    // << >>
            TK_SHIFTL, TK_SHIFTR,

    //&& || !
            TK_LOGAND, TK_LOGOR,  TK_LOGNOT,

    //+ - * / %
            TK_PLUS,   TK_MINUS,  TK_MUL, TK_DIV, TK_MOD,

    // ==  != > >= < <=
            TK_EQ,TK_NE,TK_GT,TK_GE,TK_LT,TK_LE,

    //= += -= *= /= %=
            TK_ASSIGN,TK_PLUS_AGN,TK_MINUS_AGN,TK_MUL_AGN,TK_DIV_AGN,TK_MOD_AGN,

    //, ( ) { } [ ] .
            TK_COMMA,TK_LPAREN,TK_RPAREN,TK_LBRACE,TK_RBRACE,TK_LBRACKET,TK_RBRACKET,TK_DOT,

    //if else true false while for null func return break continue new
            KW_IF,KW_ELSE,KW_TRUE,KW_FALSE,KW_WHILE,KW_FOR,KW_NULL,KW_FUNC,KW_RETURN,KW_BREAK,KW_CONTINUE,KW_NEW,

    //extern import go  struct new
            KW_EXTERN,KW_IMPORT,KW_GO,KW_STRUCT

};

/**
 * 动态变量类型定义
 */
typedef struct core_value
{
    long type;
    void* data;
}Value;


Value* value_plus(Value* lhs,Value* rhs);
char*  value_string_plus(Value* lhs,Value* rhs);
long   value_int_plus(Value* lhs,Value* rhs);


Value* value_minus(Value* lhs,Value* rhs);
char*  value_string_minus(Value* lhs,Value* rhs);
long   value_int_minus(Value* lhs,Value* rhs);

Value* value_mul(Value* lhs,Value* rhs);
char*  value_string_mul(Value* lhs,Value* rhs);
long   value_int_mul(Value* lhs,Value* rhs);

Value* value_equal(Value* lhs,Value* rhs);
int    value_string_equal(Value* lhs,Value* rhs);
int    value_int_equal(Value* lhs,Value* rhs);

Value* binaryOper(int opt, Value *lhs, Value* rhs);

#endif //LANG_TYPE_H
