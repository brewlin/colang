/**
 *@ClassName AsmGenVar
 *@Author brewlin
 *@Date 2020/10/10 0010 下午 4:48
 *@Version 1.0
 **/
#include "AsmGen.h"
#include <sstream>
using namespace std;
/**
 * 注册所有的静态字符串
 */
void AsmGen::registerStrings()
{
    for(auto &var:rt->strs){
        stringstream ss;
        string r;
        ss << ".L.." << count++;
        ss >> r;
        var->name = r;
        CreateGlobalString(var);
    }

}
/**
 * 创建全局字符串
 * @param expr
 */
void AsmGen::CreateGlobalString(StringExpr *var)
{
    //默认全局变量
//    writeln("  .globl %s", var->name.c_str());

//    writeln("  .data");
//    writeln("  .type %s, @object", var->name.c_str());
//    writeln("  .size %s, %d", var->literal.c_str(), var->literal.length());
//    writeln("  .align %d", 1);
    writeln("%s:", var->name.c_str());
    writeln("  .string \"%s\"",var->literal.c_str());
}
/**
 * 加载变量 计算变量
 * @param expr
 */
void AsmGen::GenAddr(IdentExpr *var)
{
    // 局部变量 的栈偏移量之前就已经计算出来了 这里只需要
    if (node->var->is_local) {
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
            println("  movsd (%%rax), %%xmm0");
        case Char:
            println("  %sbl (%%rax), %%eax", insn);
        case Int:
            println("  movsxd (%%rax), %%rax");
        default:
            println("  mov (%%rax), %%rax");
    }

}
