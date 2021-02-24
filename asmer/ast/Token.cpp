/**
 *@ClassName Token
 *@Author brewlin
 *@Date 2020/12/23 0023 上午 9:35
 *@Version 1.0
 **/
#include "Token.h"
namespace asmer{
    std::string tk_to_string(Token tk){
        switch(tk){
            case KW_MOV:
                return "mov";
            case KW_CMP:
                return "cmp";
            case KW_SUB:
                return "sub";
            case KW_ADD:
                return "add";
            case KW_MUL:
                return "mul";
            case KW_LEA:
                return "lea";
            case KW_CALL:
                return "call";
            case KW_INT:
                return "int";
            case KW_DIV:
                return "div";
            case KW_NEG:
                return "neg";
            case KW_INC:
                return "inc";
            case KW_DEC:
                return "dec";
            case KW_JMP:
                return "jmp";
            case KW_JE:
                return "je";
            case KW_JG:
                return "jg";
            case KW_JL:
                return "jl";
            case KW_JLE:
                return "jle";
            case KW_JNE:
                return "jne";
            case KW_JNA:
                return "jna";
            case KW_PUSH:
                return "push";
            case KW_POP:
                return "pop";
            case KW_RET:
                return "ret";
            case KW_RAX:
                return "rax";
            case KW_RCX:
                return "rcx";
            case KW_RDX:
                return "rdx";
            case KW_RBX:
                return "rbx";
            case KW_RSP:
                return "rsp";
            case KW_RBP:
                return "rbp";
            case KW_RSI:
                return "rsi";
            case KW_RDI:
                return "rdi";
            case KW_R8:
                return "r8";
            case KW_R9:
                return "r9";
            case KW_R10:
                return "r10";
            case KW_RIP:
                return "rip";
            default:
                return "unknown";
        }
    }
}
