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
    const char *insn = "movz";

    switch (type){
        case Double:
//            writeln("  movsd (%%rax), %%xmm0");
//            return;
        case Char:
//            writeln("  %sbl (%%rax), %%eax", insn);
//            return;
        case Int:
//            writeln("  movsxd (%%rax), %%rax");
//            return;
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
        default:
            writeln("  cmp $0, %%eax");
            return;
    }
}
void AsmGen::PushS(const char *arg)
{
    writeln("  push %s",arg);
}
void AsmGen::Push()
{
    writeln("  push %%rax");
}
void AsmGen::Pop(const char *arg)
{
    writeln("  pop %s",arg);
}
/**
 * 加载函数调用参数，这些参数都已经作为本地变量保存在栈上了
 * 这里要做的就是将他们加载到寄存器中
 * 1. 达到6个参数则用 DI, RSI,RDX, RCX, R8 and R9 寄存器.
 * 每个参数占 8字节
 * TODO: 只支持 int
 * @return
 */
int AsmGen::Push_arg(Runtime *rt,std::deque<Context *> prevCtxChain,std::vector<Expression *> &args)
{
    int stack = 0, gp = 0, fp = 0;

    //尽可能的加载跟多参数到寄存器  需要倒序
    for (int i = args.size() - 1; i >= 0; i--) {
        //栈参数
        if (gp++ >= GP_MAX) {
            stack++;
        }
        //读取每个变量到rax寄存器上
        args[i]->asmgen(rt,prevCtxChain);
        Push();
    }
//    if (stack % 2 == 1) {
//        writeln("  sub $8, %%rsp");
//        stack++;
//    }
    return stack;
}