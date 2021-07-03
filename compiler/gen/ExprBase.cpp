/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"

//===---------------------------------------------------------------------===//
// 计算所有的表达式 并返回一个 void  结构，

void  NullExpr::asmgen(std::deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Null,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Null);

}
void  BoolExpr::asmgen(std::deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Bool,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Bool);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,25);
}
void  CharExpr::asmgen(
                         std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    Internal::newobject(Char,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Char);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,16);

}

void  IntExpr::asmgen( std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    Internal::newobject(Int,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld,%%rdi",Int);
//    AsmGen::writeln("    mov %%rdi, (%%rax)");
//    AsmGen::writeln("    mov $%ld,%%rdi",this->literal);
//    AsmGen::writeln("    mov %%rdi, %d(%%rax)", this->literal,4);

}

void  DoubleExpr::asmgen(std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Double,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Double);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,8);
}

void  StringExpr::asmgen(std::deque<Context*> ctx) {

//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    //string类型 传的是地址 需要调用方构造
    AsmGen::writeln("    lea %s(%%rip), %%rsi", name.c_str());
    Internal::newobject(String,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld,%%rdi",String);
//    AsmGen::writeln("    mov %%rdi, (%%rax)", String);
//
//    AsmGen::writeln("    lea %s(%%rip), %%rdi", name.c_str());
//    AsmGen::writeln("    mov %%rdi, %d(%%rax)", 17);
}