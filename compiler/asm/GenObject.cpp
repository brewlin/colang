/**
 *@ClassName AsmGenFunc
 *@Author brewlin
 *@Date 2020/10/12 0012 下午 2:26
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Log.h"
#include "Block.h"
#include "Parser.h"


/**
 *
 */
void AsmGen::registerObjects()
{
    Debug("register objects")
    for(auto p :parser->pkg->classes){
        registerObjectFuncs(p.second);
    }

}
void AsmGen::registerObjectFuncs(Class* c)
{
    for(auto p : c->funcs){
        //兼容闭包函数
        for(auto* closure : p->closures){
            std::string funcname = "func_" + std::to_string(Function::closureidx ++);
            closure->receiver->varname = p->parser->getpkgname() + "_" + funcname;
            closure->parser = p->parser;
            closure->name   = funcname;
            //递归去创建
            registerFunc(closure);
        }
        currentFunc = p;
        CreateFunction(p,c);
        currentFunc = nullptr;
    }


}
