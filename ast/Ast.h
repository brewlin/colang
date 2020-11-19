/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef LANG_AST_H
#define LANG_AST_H

#include "do.h"
#include <string>


using std::string;
struct Expression;
struct Statement;

struct AstNode{

    explicit AstNode(int line,int column)
    :line(line),column(column){}
    virtual ~AstNode() = default;
    virtual std::string toString()
    {
        return "AstNode()";
    }
    int line   = -1;
    int column = -1;
};



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

    //extern import go  struct new  package
    KW_EXTERN,KW_IMPORT,KW_GO,KW_STRUCT,KW_PACKAGE

};




#endif //LANG_AST_H
