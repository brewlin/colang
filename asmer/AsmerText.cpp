/**
 *@ClassName AsmerText
 *@Author brewlin
 *@Date 2020/12/16 0016 下午 4:08
 *@Version 1.0
 **/

#include "Asmer.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"


using namespace asmer;

/**
 * 更新代码段中的可重定向
 */
void Asmer::updateText() {
    for(auto it : paser->funcs){
        Function* func = it.second;
        updateTextFunc(func);
    }

}
/**
 *
 * @param func
 */
void Asmer::updateTextFunc(asmer::Function *func) {
    for(auto it : func->instroucts){
        Instruct* inst = it.second;
        //表示当前指令集 含有可重定向引用，需要更新地址
        //这么做的主要原因是，我们第一遍扫描的时候可能当前符号在文件后方
        //等全部扫描完后再次来更新之前的值
        if(inst->is_rel){
            Sym* sym = paser->symtable->getSym(name);
            //获得该符号的偏移量地址
            inst->inst->imm32 = sym->addr;
        }

    }

}
