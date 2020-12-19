#include "Asmer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"
#include "Utils.h"

/**
 * 1. 翻译机器指令写入elf文件
 * 2. 对外部符号进行重定位记录
 */
void Asmer::InstGen() {
    std::cout << "[writeElf] .text:" << std::endl;
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto func : parser->funcs){
        std::cout << "[writeElf] .text: func:" << func->labelname <<  std::endl;
        //这里需要将函数名加入符号表
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            //进行代码段指令翻译生成
            inst->gen();
        }
    }
}
/**
 * 只计算偏移量
 */
void Asmer::InstUpdate(){
    //这里是计算指令段了，所以需要清空之前的计数
    asmer::curAddr = 0;

    cout << "text-start:" << asmer::curAddr << endl;
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto func : parser->funcs){

        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->labelname,false);
        //当前非外部符号
        parser->symtable->addSym(sym);
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            Token token = inst->type;
            if( token >= KW_MOV && token <= KW_LEA )
                InstUpdate2p(inst);
            else if( token >= KW_CALL && token <= KW_POP )
                InstUpdate1p(inst);
            else if(token == KW_RET)
                InstUpdate0p(inst);
            else
                parse_err("[InstUpdate] unknow instuct\n");
        }
    }
    cout << "text-end:" << asmer::curAddr << endl;
}


void Asmer::InstUpdate2p(Instruct *inst) {

    switch(inst->modrm->mod)
    {
        case -1://reg,imm
            switch(inst->type)
            {
                case KW_MOV:
                case KW_CMP:
                case KW_ADD:
                case KW_SUB:
                    //1字节
                    asmer::curAddr += 1;
                    break;
                default:
                    break;
            }
            //寄存器一定是8位
            asmer::curAddr += 8;
            break;
        case 0://[reg],reg reg,[reg]

            asmer::curAddr += 1;
            if(inst->modrm->mod != -1){
                //有效
                asmer::curAddr += 1;
            }
            if(inst->modrm->rm == 5)//[disp32]
            {
                asmer::curAddr += inst->inst->dispLen;
            }
            else if(inst->modrm->rm == 4 && inst->sib->scale != -1)//SIB
            {
                asmer::curAddr += 1;
            }
            break;
        case 1://[reg+disp8],reg reg,[reg+disp8]
            asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                asmer::curAddr += 1;
            if(inst->modrm->rm == 4 && inst->sib->scale != -1)//SIB
                    asmer::curAddr += 1;

            asmer::curAddr += inst->inst->dispLen;
            break;
        case 2://[reg+disp32],reg reg,[reg+disp32]
            asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                asmer::curAddr += 1;
            if(inst->modrm->rm == 4 && inst->sib->scale != -1)//SIB
                asmer::curAddr += 1;

            asmer::curAddr += inst->inst->dispLen;
            break;
        case 3://reg,reg
            asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                asmer::curAddr += 1;
            break;
    }
}

void Asmer::InstUpdate1p(Instruct *inst) {
    if(inst->type == KW_CALL || inst->type >= KW_JMP && inst->type <= KW_JNA)
    {
        //统一使用长地址跳转，短跳转不好定位
        if(inst->type == KW_CALL  || inst->type == KW_JMP)
            asmer::curAddr += 1;
        else
        {
            asmer::curAddr += 1;
            asmer::curAddr += 1;
        }
        asmer::curAddr += 8;
    }
    else if(inst->type == KW_INT)
    {
        asmer::curAddr += 1;
        asmer::curAddr += 1;
    }
    else if(inst->type == KW_PUSH)
    {
        if(inst->left == TY_IMMED)
        {
            asmer::curAddr += 1;
            asmer::curAddr += 8;
        }
        else
        {
            asmer::curAddr += 1;
        }
    }
    else if(inst->type == KW_INC)
    {
        asmer::curAddr += 1;
    }
    else if(inst->type == KW_DEC)
    {
        asmer::curAddr += 1;
    }
    else if(inst->type == KW_NEG)
    {
        asmer::curAddr += 1;
        asmer::curAddr += 1;
    }
    else if(inst->type == KW_POP)
    {
        asmer::curAddr += 1;
    }
    else if(inst->type == KW_MUL || inst->type == KW_DIV)
    {
        asmer::curAddr += 1;
        asmer::curAddr += 1;
    }
}

void Asmer::InstUpdate0p(Instruct *inst) {
    asmer::curAddr += 1;
}
