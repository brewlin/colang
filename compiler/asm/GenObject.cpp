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
    for(auto p :parser->classs){
        registerObjectFuncs(p.second);
    }

}
void AsmGen::registerObjectFuncs(Class* c)
{
    for(auto p : c->funcs){
        currentFunc = p;
        CreateFunction(p,c);
        currentFunc = nullptr;
    }


}
