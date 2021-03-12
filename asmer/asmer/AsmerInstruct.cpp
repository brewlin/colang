#include "Asmer.h"
#include "asmer/ast/Function.h"
#include "Instruct.h"
#include "asmer/ast/Sym.h"
#include "Log.h"

/**
 * 对指令直接写入文件
 */
void Asmer::InstWrite() {
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

