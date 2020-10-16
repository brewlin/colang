/**
 *@ClassName AsmGenReg
 *@Author brewlin
 *@Date 2020/10/16 0016 上午 9:01
 *@Version 1.0
 **/

#include "AsmGen.h"
/**
* 加载变量 计算变量
* @param expr
*/
void AsmGen::GenAddr(IdentExpr *var)
{
    // 局部变量 的栈偏移量之前就已经计算出来了 这里只需要
    if (var->is_local) {
        writeln("  lea %d(%%rbp), %%rax", var->offset);
        return;
    }
    // 全局变量 直接根据标号来引用即可
    writeln("  lea %s(%%rip), %%rax", var->name.c_str());

}
/**
 *
 * @param type
 */
void AsmGen::Load(ValueType type)
{
    char *insn = "movz";

    switch (type){
        case Double:
            writeln("  movsd (%%rax), %%xmm0");
            return;
        case Char:
            writeln("  %sbl (%%rax), %%eax", insn);
            return;
        case Int:
            writeln("  movsxd (%%rax), %%rax");
            return;
        default:
            writeln("  mov (%%rax), %%rax");
            return;
    }

}
/**
 * @param type
 */
void AsmGen::CreateCmp(ValueType type)
{
    switch (type) {
        case Int:
        case Char:
        case Bool:
            writeln("  cmp $0, %%eax");
            return;
        case Double:
            writeln("  xorpd %%xmm1, %%xmm1");
            writeln("  ucomisd %%xmm1, %%xmm0");
            return;
    }
}
void AsmGen::Push()
{
    writeln("  push %%rax");
}
void AsmGen::Pop(char *arg)
{
    writeln("  pop %s",arg);

}
