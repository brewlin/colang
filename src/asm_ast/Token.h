#ifndef CO_LANG_ASMER_TOKEN_H
#define CO_LANG_ASMER_TOKEN_H

namespace asmer
{
    
enum Token {
    INVALID = 0, TK_EOF,
    KW_COMM,
    KW_STRING,
    KW_GLOBAL,
    KW_TEXT,
    KW_TYPE,
    KW_LABEL,

    KW_PUSH,
    KW_POP,
    KW_MOV,
    KW_SUB,
    KW_CALL,
    KW_RET,
    KW_LEA,
    KW_CMP,
    KW_JE,

    KW_RAX,
    KW_RBX,
    KW_RCX,
    KW_RDX,
    KW_RDI,
    KW_RSI,
    KW_R8,
    KW_R9,
    KW_R10,
    KW_RSP,
    KW_RBP,

    TK_NUMBER, // int
    TK_DOUBLE, // double
    TK_STRING, // string
    TK_DOT,    // .
    TK_COLON,  // :
    TK_COMMA,  // ,
    TK_MUL,    // *
    TK_AT,     // @
    TK_IMME,   // $ immediate
    TK_SUB,    // -
    TK_REM,    // %
    TK_LPAREN, // (
    TK_RPAREN, // )
};

};
#endif //CO_LANG_TOKEN_H
