/**
 *@ClassName Instruct
 *@Author brewlin
 *@Date 2020/12/16 0016 下午 4:32
 *@Version 1.0
 **/
#include "Asmer.h"
#include <iomanip>
#include "../src/asm_ast/Instruct.h"
#include "../src/asm_ast/Token.h"
#include "Utils.h"
#include <climits>
#include <cstring>

namespace asmer{

bool Instruct::ready = false;
    

static unsigned short int opcode2[]=
    {
        //r,r   rm,r    r,rm    im,r
        0x4889, 0x488b, 0x4889, 0x48c7,//mov
        0x4839, 0x483b, 0x4839, 0x4883,//cmp
        0x4829, 0x482b, 0x4829, 0x4883,//sub
        0x4801, 0x4803, 0x4801, 0x4883,//add
        0x0000, 0x0000, 0x0000, 0x486b,//imul
        0x488d, 0x488d, 0x488d, 0x488d//lea
    };
static unsigned short int opcode1[]=
    {
        //CALL INT  DIV  NEG  INC  DEC  JMP,
        0xe8,  0xcd,0xf7,0x40,0x48,0x00,0xe9,
        //JE   JG     JL     JLE    JNE  JNA
        0x74,0x7f,0x0f8c,0x7e,0x55,0x0f86,
        //PUSH INT POP
        0x50,0x58
    };
static unsigned char opcode0[]=
    {
        //RET
        0xc3
    };
void Instruct::append(unsigned char b) {
    //第一次单纯的收集label标签，并计算偏移量
    //第二次才是实际写入指令
    if(ready)
        bytes[size++] = b;
    asmer::curAddr += 1;
}
void Instruct::append(unsigned short int b) {
    append((unsigned char)(b >> 8));
    append((unsigned char)(b));
}
void Instruct::append(unsigned long int b, int len) {
    for(int i = 0; i < len ; i ++ ){
        append((unsigned char)(b >> (8*i)));
    }
}
/*
 * 输出ModRM字节
 * mod(2)|reg(3)|rm(3)
*/
void Instruct::writeModRM() {
    if(modrm->mod != -1)//有效
    {
        unsigned char mrm = (unsigned char)(((modrm->mod & 0x00000003)<<6)+((modrm->reg & 0x0000007) << 3)+(modrm->rm & 0x00000007));
        append(mrm);
//        printf("[writeModrm: 0x%08x\n",mrm);
    }
}
/*
	输出SIB字节
	scale(2)|index(3)|base(3)
*/
void Instruct::writeSIB() {
    if(sib->scale != -1)
    {
        unsigned char _sib=(unsigned char)(((sib->scale&0x00000003)<<6)+((sib->index&0x00000007)<<3)+(sib->base&0x00000007));
        append(_sib);
//        printf("输出SIB=0x%08x\n",_sib);
    }
}

bool Instruct::updateRel() {

    bool flag = false;
    //如果没有引用就返回
    if(name == "") return flag;

    Sym* sym  = Asmer::obj->parser->symtable->getSym(name);
    //表示数据的引用
    if(!is_func)//绝对重定位
    {
//        if(ready && sym->externed){
        // 1. lea L0(%rip), %rax 需要重定位的数据
        // 2. jmp L2            不需要重定位的本地标签
        // is_rel 正是区分这种情况
        if(ready && is_rel){
            Asmer::elf->addRel(".text",asmer::curAddr,name,R_X86_64_PC32);
            flag = true;
        }
    }
    else if(is_func)//相对重定位
    {
        //如果当前指令有函数标签，说明是函数调用
        //外部函数
        if(ready){
//         if(ready && sym->externed){
            //R_X86_64_REX_GOTP  42
            Asmer::elf->addRel(".text",asmer::curAddr,name,42);
            flag = true;
         }
    }
    return flag;
}
void Instruct::gen2Op() {
    int index = -1;
    //立即数 默认1字节
    int len   = 1;
    if(left == TY_IMMED)//鉴别操作数种类
        index = 3;
    else
        index = (right -2) * 2 + left - 2;
    //计算所在索引
    index = (type - KW_MOV ) * 4  + index;
    //附加指令名称和长度
    unsigned short int opcode = opcode2[index];
    unsigned char exchar;
    switch(modrm->mod)
    {
        //表示立即数操作 如: mov $100,%rax
        case -1:
            switch(type)
            {
                //0xc0 + 寄存器索引
                case KW_MOV:{
                    //如果立即数 大于32位则mov指令有点不一样
                    if(inst->imm > INT_MAX){
                        len = 8;
                        opcode = 0x48b8 + (unsigned char)(modrm->reg);
                        append(opcode);
                        append(inst->imm,len);
                        return;
                    }else{
                        len = 4;
                        exchar = 0xc0 + (unsigned char)(modrm->reg);
                    }
                    //兼容gnu assmebley 语法
                    //mov label@GOTPCREL(%rip),%rax
                    //mov label(%rip),%rax
                    if(left == TY_REL){
                        opcode = 0x488b;
                        //如果右边寄存器大于 %r8
                        if(tks[0] >= KW_R8){
                            opcode = 0x4c8b;
                        }
                        exchar = 0x05 + (unsigned char)modrm->reg * 8;
                    }
                    break;
                }
                //0xf8 + 寄存器索引
                case KW_CMP:{

                    //立即数小于 1字节signed char则只需要一个字节
                    if(inst->imm > SCHAR_MAX){
                        len = 4;
                        opcode = 0x4881;
                    }
                    exchar = 0xf8;
                    exchar += (unsigned char)(modrm->reg);
                    break;
                }
                //0xc0 + 寄存器索引
                case KW_ADD:{
                    //立即数大于于 1字节，操作数指令不一样
                    if(inst->imm > SCHAR_MAX){
                        len = 4;
                        opcode = 0x4881;
                    }//其他情况 opcode = 0x4883
                    exchar = 0xc0;
                    exchar += ( unsigned char )(modrm->reg);
                    break;
                }
                //0xe8 + 寄存器索引
                case KW_SUB:{
                    //立即数大于于 1字节，操作数指令不一样
                    if(inst->imm > SCHAR_MAX){
                        len = 4;
                        opcode = 0x4881;
                    }//其他情况 opcode = 0x4883
                    exchar = 0xe8;
                    exchar += ( unsigned char)(modrm->reg);
                    break;
                }case KW_MUL:{
                    exchar = 0xc0;
                    exchar += (unsigned char)(modrm->reg) * 0x09;
                    break;
                }
                //可能是 lea variable(%rip),%rax
                case KW_LEA:{
                    //判断是否是引用
                    if(left == TY_REL){
                        Sym* sym = Asmer::obj->parser->symtable->getSym(name);
                        //不是外部连接符
                        inst->imm  = 0;
                        len        = 4;
//                        if(!sym->externed){
//                            inst->imm = sym->addr;
//                        }
                        exchar = 0x05 + 0x08 * (unsigned char)modrm->reg;
                    }else{
                        std::cout << "unsupport instruct:" << asmer::tk_to_string(type) << std::endl;
                        assert(false);
                    }

                    break;
                }
                default:{
                    std::cout << "unsupport instruct:" << asmer::tk_to_string(type) << std::endl;
                    assert(false);
                }
            }
            //写入操作数
            append(opcode);
            //大于INT_MAX 不需要附加指令
            //写入附加指令
            // if(inst->imm < INT_MAX)
            append(exchar);
            //可能的重定位位置 mov eax,@buffer,也有可能是mov eax,@buffer_len，就不许要重定位，因为是宏
            updateRel();
            //写入立即数
            //一定要按照长度输出立即数
            if(is_rel){
                append(0x0,len);
                break;
            }
            append(inst->imm,len);
            break;
        //寄存器间接访问
        // mov (%rax),%rcx
        // mpv %rax,(%rcx)
        // 上面两个子类的前缀操作数是不一样的这点要区分
        case 0b00:
            append(opcode);
            writeModRM();
            //说明是rbp 寄存器操作
            if(modrm->rm == 5){
                updateRel();//可能是mov eax,[@buffer],后边disp8和disp32不会出现类似情况
                //这里给末尾在加上1字节偏移量
                //因为对于rbp的寄存器间接访问需要当做偏移量访问
                if(inst->dispLen)
                    append(inst->disp,inst->dispLen);
            }
            //说明是rsp寄存器操作 需要有sib字节进行补充
            else if(modrm->rm == 4){
                //写入一字节sib补充字段
                writeSIB();
            }
            break;
        //偏移量访问，如:
        //mov %rax,100(%rcx)
        //mov 100(%rax),%rcx
        case 0b01://8位偏移
        case 0b10://32位偏移
            switch(type){
                //处理寄存器大于r8的情况
                case KW_MOV:{
                    if(left == TY_REG && tks[0] >= KW_R8){
                        opcode = 0x4c89;
                    }
                    if(right == TY_REG && tks[0] >= KW_R8){
                        opcode = 0x4c8b;
                    }
                    //下面继续处理 后面的 morm sib部分
                    break;
                }
                case KW_SUB:{
                    //sub $1,100(%rsp)
                    if(left == TY_IMMED && right == TY_MEM) {
                        opcode = 0x8368 + (unsigned char) (modrm->rm);
                        append(opcode);
                        append(inst->disp,inst->dispLen);
                        append(inst->imm,1);
                        return;
                    }
                }
                case KW_CMP:{
                    //cmp $0,-40(%rsp) 如果右边是内存访问
                    if(left == TY_IMMED && right == TY_MEM){
                        opcode = 0x8378 + (unsigned char)modrm->rm;
                        append(opcode);
                        append(inst->disp,inst->dispLen);
                        //内存比较只支持8位
                        append(inst->imm,1);
                        return;
                    }
                }
                default:{
                }
            }
            append(opcode);
            //写入1字节modrm字段
            writeModRM();
            //rsp需要单独写入sib引导字段
            if(modrm->rm == 4)
                writeSIB();
            //写入偏移量 inst->dispLen 一般为1 或者 4
            if(inst->dispLen)
                append(inst->disp,inst->dispLen);
            break;
        //寄存器访问
        case 0b11:{
            //默认0x4889
            if(tks[0] >= KW_R8)
                opcode = 0x4c89;
            if(tks[1] >= KW_R8)
                opcode = 0x4989;
            append(opcode);
            //写入modrm字段
            writeModRM();
            break;
        }
    }
}

void Instruct::gen1Op() {
    int len  = 4 ;//默认是8
    unsigned char exchar;
    unsigned short int opcode = opcode1[type - KW_CALL];
    if(type == KW_CALL || type >= KW_JMP && type <= KW_JNA)
    {
        switch(type){
            //统一使用长地址跳转，短跳转不好定位
            case KW_CALL:{
                //1. call 标签
                if(left == TY_REL){
                    opcode = 0xe8;
                    append((unsigned char)opcode);
                }
                //寄存器间接调用
                if(left == TY_REG){
                    if(tks[0] < KW_R8){
                        //2. call 通用寄存器
                        opcode = 0xff;
                        append((unsigned char)opcode);
                        //写入寄存器索引
                        unsigned  char reg = 0xd0 + (unsigned char)modrm->reg;
                        append(reg);
                    }else{
                        //3. call r8-r15寄存器
                        opcode = 0x41ff;
                        append(opcode);
                        exchar = 0xd0 + modrm->reg;
                        append(exchar);
                    }
                    //寄存器间调用就结束了，不需要再写入偏移量了
                    return;
                }
                break;
            }
            case KW_JMP:{
                //判断是不是内部符号
                bool is_internal = true;
                 if(is_func){
                    Sym* sym  = Asmer::obj->parser->symtable->getSym(name);
                    if(sym->externed)
                        is_internal = false;
                 }
                if(is_internal){
                    //1. 内部符号 eb
                    opcode = 0xeb;
                    //内部跳转默认1字节
                    len = 1;
                }else{
                    //2. 外部符号 e9 00 00 00 00
                    opcode = 0xe9;
                }
                //1字节
                append((unsigned char)opcode);
                //jmp后面不需要再
                break;
            }
            //如果外部符号则 默认当前操作数
            //当前符号则74
            case KW_JE:{
                opcode = 0x0f84;
                append(opcode);
                updateRel();
                Sym* sym = Asmer::obj->parser->symtable->getSym(name);
                //可能为负数
                int rel = sym->addr - asmer::curAddr - 4;
                append(rel,4);
                return;
            }
            case KW_JLE:
            case KW_JG:{
                append((unsigned char)opcode);
                break;
            }
            default:{

                std::cout << "unsupoort instruct:" << asmer::tk_to_string(type) << std::endl;
                assert(false);
                append((unsigned char)(opcode >> 8),1);
                append((unsigned char)opcode);
            }
        }
        bool is_rel = updateRel();
        //处理可能的相对重定位信息，call fun,如果fun是本地定义的函数就不会重定位了
        int rel  = inst->imm - (asmer::curAddr + 4);//调用符号地址相对于下一条指令地址的偏移，因此加4
        //处理有些本地符号在第一次parser的时候由于处于后面导致 偏移量无法获得，需要再次计算
        if(left == TY_REL && inst->imm == 0){
            //写入相对偏移量
            Sym* sym = Asmer::obj->parser->symtable->getSym(name);
            //可能为负数
            rel = sym->addr - asmer::curAddr - 1;
            append(rel,1);
            return;
        }
        //存在外部引用
        if(is_rel){
            //构建4字节 0
            append(0x00000000,len);
            return;
        }
        cout << rel << ":" << len <<endl;
        append(rel,len);
    }
    else if(type == KW_INT)
    {
        append((unsigned char)opcode);
        append(inst->imm,1);
    }
    else if(type == KW_PUSH)
    {
        //1. 立即数 push
        if(left == TY_IMMED)
        {
            //强制使用32位立即数进行存储
            opcode = 0x6a;
            append((unsigned char)opcode);
            append(inst->imm,1);
        }
        else if(tks[0] < KW_R8)
        {
            opcode += (unsigned char)(modrm->reg);
            append((unsigned  char)opcode);
        }else{
            //要加个0x41 前缀指令
            append((unsigned  char)0x41);
            opcode +=(unsigned char)(modrm->reg);
            append((unsigned char)opcode);
        }
    }
    //TODO : supoort inc instruct
    //TODO : supoort dec instruct
    //TODO : supoort neg instruct
    else if(type == KW_INC || type == KW_DEC || type == KW_NEG || type == KW_DIV)
    {
        std::cout << "not support instruct:" << type << std::endl;
        assert(false);
    }
    else if(type == KW_POP)
    {
        //1间接访问的指令不一样
        if(left == TY_MEM){
            if(tks[0] == KW_RSP || tks[0] == KW_RBP){
                std::cout << "not support instruct:" << tks[0] << std::endl;
                assert(false);
            }
            opcode = 0x8f;
            append((unsigned char)opcode);
            //写入寄存器索引
            append((unsigned char)modrm->reg);
        //TODO: 支持偏移量访问如: pop 10(%rax)
        //2寄存器访问
        }else{
            //TODO: 支持 pop (%rsp) | pop (%rbp)
            //%r8 以上需要加上前缀指令
            if(tks[0] >= KW_R8){
                append((unsigned char)0x41,1);
            }
            opcode += (unsigned char)(modrm->reg);
            append((unsigned  char)opcode,1);
        }
    }

}

void Instruct::gen0Op() {
    unsigned char opcode = opcode0[0];
    append(opcode);
}
void Instruct::gen(){
    Token token = type;
    if( token >= KW_MOV && token <= KW_LEA )
        gen2Op();
    else if( token >= KW_CALL && token <= KW_POP )
        gen1Op();
    else if(token == KW_RET)
        gen0Op();
    else
        parse_err("[instruct gen] unknow instuct\n");
}



};
