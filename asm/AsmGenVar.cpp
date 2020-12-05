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
    for(auto &var:parser->strs){
        stringstream ss;
        string r;
        ss << ".L.." << count++;
        ss >> r;
        var->name = r;
        CreateGlobalString(var);
    }

}
void AsmGen::registerVars()
{
    for(auto &var:parser->gvars){
        string name  = var.first;
        string gname = parser->getpkgname() + "." + name;
        writeln("  .comm   %s,8,8",gname.c_str());
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
