#include "Asmer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"

void Asmer::InstGen() {
    for(auto it : paser->funcs){
        Function* func = it.second;

        for(auto inst : func->instructs){
            inst->gen();
        }
    }
}