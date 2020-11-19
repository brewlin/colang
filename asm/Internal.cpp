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
    //第二个参数 lhs 在栈顶的
    AsmGen::writeln("  mov (%%rsp),%rsi");
    //第三个参数 rhs 在rax寄存器的
    AsmGen::writeln("  mov %%rax, %%rdx");
    call("binaryOper");
}
void Internal::gc_malloc()
{
    AsmGen::writeln("  mov $%ld, %%rdi", sizeof(CoreValue));
    call("malloc");
}
/**
 * @return
 */
void Internal::newobject(int type, long data)
{
    AsmGen::writeln("  push %%rdi");
    AsmGen::writeln("  push %%rsi");

    AsmGen::writeln("  mov $%ld, %%rdi", type);
    if(type != String)
        AsmGen::writeln("  mov $%ld, %%rsi", data);

    call("newobject");

    AsmGen::writeln("  pop %%rsi");
    AsmGen::writeln("  pop %%rdi");
}
void Internal::isTrue()
{
    AsmGen::writeln("  mov %%rax, %%rdi");
    call("isTrue");
}
void Internal::get_object_value()
{
    AsmGen::writeln("  push %%rdi");
    AsmGen::writeln("  mov %%rax, %%rdi");
    call("get_object_value");
    AsmGen::writeln("  pop %%rdi");
}
void Internal::call(std::string funcname)
{
    AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
    AsmGen::writeln("  mov %%rax, %%r10");
    AsmGen::writeln("  mov $%d, %%rax", 0);
    AsmGen::writeln("  call *%%r10");
}
