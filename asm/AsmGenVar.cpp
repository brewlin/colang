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
    for(auto &sexpr:rt->strs){
        stringstream ss;
        ss << ".L.." << count++;
        StringExpr* var = dynamic_cast<StringExpr*>(sexpr);
        string r;
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
    writeln("  .globl %s", var->name.c_str());

    writeln("  .data");
    writeln("  .type %s, @object", var->name.c_str());
    writeln("  .size %s, %d", var->name.c_str(), var->name.length());
    writeln("  .align %d", 1);
    writeln("%s:", var->name.c_str());
    writeln("  .string %s",var->name.c_str());
}
