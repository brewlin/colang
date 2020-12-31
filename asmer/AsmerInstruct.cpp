#include "Asmer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"
#include "Log.h"

/**
 * 1. 翻译机器指令写入elf文件
 * 2. 对外部符号进行重定位记录
 */
void Asmer::InstCollect() {
    //这里是计算指令段了，所以需要清空之前的计数
    Debug("instructs collection");
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto func : parser->funcs){
        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->labelname,false);
        //当前非外部符号
        //这里需要将函数名加入符号表
        parser->symtable->addSym(sym);
        Debug("labelname:%s offset:%d",func->labelname,sym->addr);
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            //进行代码段指令翻译生成
            inst->gen();
        }
    }
}
/**
 * 对指令直接写入文件
 */
void Asmer::InstWrite() {
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto func : parser->funcs){
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            // printf("%s : ",inst->str.c_str());
            // for(int i = 0; i < inst->size ; i ++){
                // printf("%x ",(unsigned char)inst->bytes[i]);
            // }
            // std::cout << std::endl;
            writeBytes(inst->bytes,inst->size);
        }
    }
}

