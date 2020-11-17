#include "Internal.h"
#include "AsmGen.h"
/**
 * rsp 栈顶是 lhs
 * rax 寄存器是 rhs
 * binaryOper(opt,lhs,rhs) 只有三个参数
 * "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r10"
 * @param opt
 */
void Internal::CallOperator(Token opt) {
    //这里需要调用calculate来及计算赋值
    // assign(this->opt,f->locals[varExpr->identname],rhs);
//        call_binary_oper(this->opt);
    //第一个参数 opt
    AsmGen::writeln("  mov $%ld, %%rdi", opt);
    //第二个参数 lhs
    AsmGen::Pop("%rsi");
    AsmGen::PushS("%rsi");
    //第三个参数 rhs
    AsmGen::writeln("  mov %%rax, %%rdx");
    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", "binaryOper");
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
    AsmGen::writeln("  add $%d, %%rsp", 0);
}
void Internal::gc_malloc()
{

    AsmGen::writeln("  mov $%ld, %%rdi", sizeof(CoreValue));
    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", "malloc");
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
    AsmGen::writeln("  add $%d, %%rsp", 0);
}
/**
 * @return
 */
void Internal::newobject(int type, long data)
{
    AsmGen::writeln("  mov $%ld, %%rdi", type);
    if(type != String)
        AsmGen::writeln("  mov $%ld, %%rsi", data);

    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", "newobject");
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
}
void Internal::isTrue()
{
    AsmGen::writeln("  mov %%rax, %%rdi");

    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", "isTrue");
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
}
void Internal::get_object_value()
{


    AsmGen::writeln("  push %%rdi");
    AsmGen::writeln("  mov %%rax, %%rdi");

    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", "get_object_value");
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
    AsmGen::writeln("  pop %%rdi");
}
