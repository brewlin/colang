#include "Asmer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"
#include "Utils.h"

/**
 * 1. 翻译机器指令写入elf文件
 * 2. 对外部符号进行重定位记录
 */
void Asmer::InstCollect() {
    //这里是计算指令段了，所以需要清空之前的计数
//    asmer::curAddr = 0;
//    std::cout << "[buildElf] .text:" << std::endl;
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto func : parser->funcs){
//        std::cout << "[buildElf] .text: func:" << func->labelname <<  std::endl;
        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->labelname,false);
        //当前非外部符号
        parser->symtable->addSym(sym);
        // cout << func->labelname << ":" << asmer::curAddr << ":" << sym->addr << endl;
        //这里需要将函数名加入符号表
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            //进行代码段指令翻译生成
            inst->gen();
        }
//        cout << "text-end:" << asmer::curAddr << endl;
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

