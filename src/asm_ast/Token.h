#ifndef CO_LANG_ASM_TOKEN_H
#define CO_LANG_ASM_TOKEN_H

namespace asm
{
    
enum Token {
    INVALID = 0, TK_EOF,
    KW_COMM,
    KW_GLOBAL,
    KW_TEXT,
    KW_TYPE,
    KW_STRING,

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
    
    KW_LABEL,
    TK_NUMBER,
    TK_COLON, 
    TK_COMMA,
};

};
#endif //CO_LANG_TOKEN_H
