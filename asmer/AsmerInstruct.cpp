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
    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto it : paser->funcs){
        Function* func = it.second;

        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->name);
        paser->symtable->addSym(sym)
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
    Asmer::curAddr = 0;

    //这里其实是属于新的段了，curAddr 段大小需要从0开始计数， 但是datalen是持续累加的
    for(auto it : paser->funcs){
        Function* func = it.second;

        //这里需要将函数名加入符号表
        Sym* sym = new Sym(func->name);
        paser->symtable->addSym(sym)
        //接下来解析函数区域所有的指令
        for(auto inst : func->instructs){
            Token token = inst->inst->type;
            if( token >= KW_MOV && token <= KW_LEA )
                InstUpdate2p(inst);
                gen2Op();
            else if( token >= KW_CALL && token <= KW_POP )
                InstUpdate1p(inst);
            else if(token == KW_RET)
                InstUpdate0p(inst);
            else
                parse_err("[InstUpdate] unknow instuct\n");
        }
    }
}


void Asmer::InstUpdate2p(Instruct *inst) {

    switch(inst->modrm->mod)
    {
        case -1://reg,imm
            switch(type)
            {
                case KW_MOV:
                case KW_CMP:
                case KW_ADD:
                case KW_SUB:
                    //1字节
                    Asmer::curAddr += 1;
                    break;
                default:
                    break;
            }
            //寄存器一定是8位
            Asmer::curAddr += 8;
            break;
        case 0://[reg],reg reg,[reg]

            Asmer::curAddr += 1;
            if(inst->modrm->mod != -1){
                //有效
                Asmer::curAddr += 1;
            }
            if(inst->modrm->rm == 5)//[disp32]
            {
                Asmer::curAddr += inst->inst->dispLen;
            }
            else if(inst->modrm->rm == 4 && sib->scale != -1)//SIB
            {
                Asmer::curAddr += 1;
            }
            break;
        case 1://[reg+disp8],reg reg,[reg+disp8]
            Asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                Asmer::curAddr += 1;
            if(inst->modrm->rm == 4 && sib->scale != -1)//SIB
                    Asmer::curAddr += 1;

            Asmer::curAddr += inst->inst->dispLen;
            break;
        case 2://[reg+disp32],reg reg,[reg+disp32]
            Asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                Asmer::curAddr += 1;
            if(inst->modrm->rm == 4 && sib->scale != -1)//SIB
                Asmer::curAddr += 1;

            Asmer::curAddr += inst->inst->dispLen;
            break;
        case 3://reg,reg
            Asmer::curAddr += 1;
            if(inst->modrm->mod != -1)
                Asmer::curAddr += 1;
            break;
    }
}

void Asmer::InstUpdate1p(Instruct *inst) {
    if(type == KW_CALL || type >= KW_JMP && type <= KW_JNA)
    {
        //统一使用长地址跳转，短跳转不好定位
        if(type == KW_CALL  || type == KW_JMP)
            Asmer::curAddr += 1;
        else
        {
            Asmer::curAddr += 1;
            Asmer::curAddr += 1;
        }
        Asmer::curAddr += 8;
    }
    else if(type == KW_INT)
    {
        Asmer::curAddr += 1;
        Asmer::curAddr += 1;
    }
    else if(type == KW_PUSH)
    {
        if(left == TY_IMMED)
        {
            Asmer::curAddr += 1;
            Asmer::curAddr += 8;
        }
        else
        {
            Asmer::curAddr += 1;
        }
    }
    else if(type == KW_INC)
    {
        Asmer::curAddr += 1;
    }
    else if(opt == i_dec)
    {
        Asmer::curAddr += 1;
    }
    else if(type == KW_NEG)
    {
        Asmer::curAddr += 1;
        Asmer::curAddr += 1;
    }
    else if(type == KW_POP)
    {
        Asmer::curAddr += 1;
    }
    else if(type == KW_MUL || type == KW_DIV)
    {
        Asmer::curAddr += 1;
        Asmer::curAddr += 1;
    }
}

void Asmer::InstUpdateOp(Instruct *inst) {
    Asmer::curAddr += 1;
}
