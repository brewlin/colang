#include "Asmer.h"
#include "asmer/ast/Function.h"
#include "asmer/ast/Instruct.h"
#include "asmer/ast/Sym.h"
#include "Log.h"

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

