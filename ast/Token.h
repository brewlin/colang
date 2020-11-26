/**
 *@Author brewlin
 *@Date 2020/11/26 0026 上午 10:23
 *@Version 1.0
 **/
#ifndef LANG_TOKEN_H
#define LANG_TOKEN_H


#define Null   0
#define Int    1
#define Double 2
#define String 3
#define Bool   4
#define Char   5
#define Array  6
#define Map    7
#define Object 8


#define TRUE   1
#define FALSE  0
#define OK     0
#define ERROR  -1

//TYPE TOKEN
enum Token {
    //invalid identifier eof
    INVALID = 0, TK_IDENT, TK_EOF,

    //int string double char
    LIT_INT,   LIT_STR,  LIT_DOUBLE, LIT_CHAR,

    // & | ^ ~
    TK_BITAND, TK_BITOR,TK_BITXOR,TK_BITNOT ,
    // &= |=
    TK_BITAND_AGN, TK_BITOR_AGN ,

    // << >> <<= >>=
    TK_SHIFTL, TK_SHIFTR,TK_SHIFTL_AGN,TK_SHIFTR_AGN,

    //&& || !
    TK_LOGAND, TK_LOGOR,  TK_LOGNOT,

    // ==  != > >= < <=
    TK_EQ,TK_NE,TK_GT,TK_GE,TK_LT,TK_LE,

    //+ - * / %
    TK_PLUS,   TK_MINUS,  TK_MUL, TK_DIV, TK_MOD,

    //= += -= *= /= %=
    TK_ASSIGN,TK_PLUS_AGN,TK_MINUS_AGN,TK_MUL_AGN,TK_DIV_AGN,TK_MOD_AGN,

    //, ( ) { } [ ] . :
    TK_COMMA,TK_LPAREN,TK_RPAREN,TK_LBRACE,TK_RBRACE,TK_LBRACKET,TK_RBRACKET,TK_DOT,TK_COLON,

    //if else true false while for null func return break continue new
    KW_IF,KW_ELSE,KW_TRUE,KW_FALSE,KW_WHILE,KW_FOR,KW_NULL,KW_FUNC,KW_RETURN,KW_BREAK,KW_CONTINUE,KW_NEW,

    //extern import go  struct new  package dereference
    KW_EXTERN,KW_IMPORT,KW_GO,KW_STRUCT,KW_PACKAGE,TK_DELREF

};
#endif //LANG_TOKEN_H
