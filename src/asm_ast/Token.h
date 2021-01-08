#ifndef CO_LANG_ASMER_TOKEN_H
#define CO_LANG_ASMER_TOKEN_H

#include <string>
namespace asmer
{
    
enum Token {
    INVALID = 0, TK_EOF,
    KW_STRING,
    KW_QUAD,
    KW_GLOBAL,
    KW_DATA,
    KW_TEXT,
    KW_LABEL,

    // need 2 op
    KW_MOV,
    KW_CMP,
    KW_SUB,
    KW_ADD,
    KW_AND,
    KW_MUL,
    KW_LEA,

    // need 1 op
    KW_CALL,
    KW_INT,
    KW_DIV,
    KW_NEG,
    KW_INC,
    KW_DEC,
    KW_JMP,
    KW_JE,
    KW_JG,
    KW_JL,
    KW_JLE,
    KW_JNE,
    KW_JNA,
    KW_PUSH,
    KW_POP,

    //need 0 op
    KW_RET,

    KW_RAX,
    KW_RCX,
    KW_RDX,
    KW_RBX,
    KW_RSP,
    KW_RBP,
    KW_RSI,
    KW_RDI,
    KW_R8,
    KW_R9,
    KW_R10,
    KW_RIP,

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

std::string tk_to_string(Token tk);

//指令类型
//1 立即数
//2 寄存器
//3 内存地址
//4 重定位链接符号
enum InstType {
    TY_INVAL = 0,
    TY_IMMED,
    TY_REG,
    TY_MEM,
    TY_REL,
};

};
#endif //CO_LANG_TOKEN_H
