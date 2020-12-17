#include "Asmer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"

void Asmer::InstGen() {
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto it : paser->funcs){
        Function* func = it.second;

        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->name);
        paser->symtable->addSym(sym)
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            inst->gen();
        }
    }
}