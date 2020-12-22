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

namespace asmer{
    

static unsigned short int i_2opcode[]=
    {
        //r,r   rm,r    r,rm    im,r
        0x4889, 0x488b, 0x4889, 0x48c7,//mov
        0x4839, 0x483b, 0x4839, 0x4883,//cmp
        0x4829, 0x482b, 0x4829, 0x4883,//sub
        0x4801, 0x4803, 0x4801, 0x4883,//add
        0x4800, 0x488d, 0x4800, 0x4800//lea
    };
static unsigned short int i_1opcode[]=
    {
    //KW_CALL,KW_DIV,KW_NEG,KW_INC,KW_DEC,KW_JMP,KW_JE,KW_JG,KW_JL,KW_JLE,KW_JNA,KW_PUSH,KW_INT,KW_POP,
        //call,int, imul,idiv,neg, inc, dec, jmp<rel32>
        0xe8,  0xcd,0xf7,0xf7,0xf7,0x40,0x48,0xe9,
        //je,jg,jl,jge,jle,jne,jna<rel32>
        0x0f84,0x0f8f,0x0f8c,0x0f8d,0x55,0x0f85,0x0f86,
        //0xeb,//jmp rel8
        //0x74,0x7f,0x7c,0x7d,0x7e,0x75,0x76,//je,jg,jl,jge,jle,jne,jna<rel8>
        //push
        0x50,
        //pop
        0x58
    };
static unsigned char i_0opcode[]=
    {
        0xc3//ret
    };
/*
	输出ModRM字节
	mod(2)|reg(3)|rm(3)
*/
void Instruct::writeModRM() {
    if(modrm->mod != -1)//有效
    {
        unsigned char mrm = (unsigned char)(((modrm->mod & 0x00000003)<<6)+((modrm->reg & 0x0000007) << 3)+(modrm->rm & 0x00000007));
        writeBytes(mrm,1);
        printf("[writeModrm: 0x%08x\n",mrm);
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
        writeBytes(_sib,1);
        //printf("输出SIB=0x%08x\n",_sib);
    }
}
/*
	按照小端顺序（little endian）输出指定长度数据
	len=1：输出第4字节
	len=2:输出第3,4字节
	len=4:输出第1,2,3,4字节
*/
void Instruct::writeBytes(int value, int len) {

    Asmer::bytes += len;
    fwrite(&value,len,1,Asmer::obj->out);
}

bool Instruct::updateRel() {

    bool flag = false;
    //如果没有引用就返回
    if(name == "") return flag;

    //表示数据的引用
    if(!is_func)//绝对重定位
    {
        Asmer::elf->addRel(".text",asmer::curAddr,name,R_386_32);
        flag = true;
    }
    else if(is_func)//相对重定位
    {
        Sym* sym  = Asmer::obj->parser->symtable->getSym(name);
        //如果当前指令有函数标签，说明是函数调用
        //外部函数
        if(sym->externed){
            Asmer::elf->addRel(".text",asmer::curAddr,name,R_386_PC32);
            flag = true;
        }
    }
    return flag;
}
void Instruct::gen2Op() {
    //测试信息
//     cout<<"len="<<len<<"(1-Byte;4-DWord)\n";
//     cout<<"des:type="<<des_t<<"(1-imm;2-mem;3-reg)\n";
//     cout<<"src:type="<<src_t<<"(1-imm;2-mem;3-reg)\n";
    //  cout<<"ModR/M="<<modrm->mod<<" "<<modrm->reg<<" "<<modrm->rm<<endl;
    // cout<<"SIB="<<sib->scale<<" "<<sib->index<<" "<<sib->base<<endl;
    // cout<<"disp32="<<inst.disp32<<",disp8="<<(int)inst.disp8<<"(<-"<<inst.disptype<<":(0-disp8;1-disp32) imm="<<inst->imm<<endl;
    //计算操作码索引 (mov,8,reg,reg)=000 (mov,8,reg,mem)=001 (mov,8,mem,reg)=010 (mov,8,reg,imm)=011
    //(mov,32,reg,reg)=100 (mov,32,reg,mem)=101 (mov,32,mem,reg)=110 (mov,32,reg,imm)=111  [0-7]*(i_lea-i_mov)
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
    unsigned char opcode = i_2opcode[index];
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
                        //写入2字节指令 48 b8 + reg
                        writeBytes(opcode,2);
                    }else{
                        len = 4;
                        opcode += 0xc0 + (unsigned char)(modrm->reg);
                        //三字节
                        writeBytes(opcode,3);
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
                    //写入操作数
                    writeBytes(opcode,2);
                    exchar = 0xf8;
                    exchar += (unsigned char)(modrm->reg);
                    //写入附加指令
                    writeBytes(exchar,1);
                    break;
                }
                //0xc0 + 寄存器索引
                case KW_ADD:{
                    //立即数大于于 1字节，操作数指令不一样
                    if(inst->imm > SCHAR_MAX){
                        len = 4;
                        opcode = 0x4881;
                    }//其他情况 opcode = 0x4883
                    //写入操作数
                    writeBytes(opcode,2);
                    exchar = 0xc0;
                    exchar += ( unsigned char )(modrm->reg);
                    //写入附加指令
                    writeBytes(exchar,1);
                    break;
                }
                //0xe8 + 寄存器索引
                case KW_SUB:{
                    //立即数大于于 1字节，操作数指令不一样
                    if(inst->imm > SCHAR_MAX){
                        len = 4;
                        opcode = 0x4881;
                    }//其他情况 opcode = 0x4883
                    writeBytes(opcode,2);
                    exchar = 0xe8;
                    exchar += ( unsigned char)(modrm->reg);
                    writeBytes(exchar,1);
                    break;
                }
            }
            //可能的重定位位置 mov eax,@buffer,也有可能是mov eax,@buffer_len，就不许要重定位，因为是宏
            updateRel();
            writeBytes(inst->imm,len);//一定要按照长度输出立即数
            break;
        //寄存器间接访问
        // mov (%rax),%rcx
        // mpv %rax,(%rcx)
        // 上面两个子类的前缀操作数是不一样的这点要区分
        case 0:
            writeBytes(opcode,2);
            writeModRM();
            //说明是rbp 寄存器操作
            if(modrm->rm == 5){
                updateRel();//可能是mov eax,[@buffer],后边disp8和disp32不会出现类似情况
                //这里给末尾在加上1字节偏移量
                //因为对于rbp的寄存器间接访问需要当做偏移量访问
                inst->writeDisp();
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
        case 1:
        case 2:
            writeBytes(opcode,2);
            //写入1字节modrm字段
            writeModRM();
            //rsp需要单独写入sib引导字段
            if(modrm->rm == 4)
                writeSIB();
            //写入偏移量 inst->dispLen 一般为1 或者 4
            inst->writeDisp();
            break;
        //寄存器访问
        case 3:
            writeBytes(opcode,2);
            //写入modrm字段
            writeModRM();
            break;
    }
}

void Instruct::gen1Op() {
    int len  = 8 ;//默认是8
    unsigned char exchar;
    unsigned short int opcode = i_1opcode[type - KW_CALL];
    if(type == KW_CALL || type >= KW_JMP && type <= KW_JNA)
    {
        bool is_rel = updateRel();//处理可能的相对重定位信息，call fun,如果fun是本地定义的函数就不会重定位了
        switch(type){
            //统一使用长地址跳转，短跳转不好定位
            case KW_CALL:{
                //1. call 标签
                if(left == TY_REL){
                    opcode = 0xe8;
                    writeBytes(opcode,1);
                }
                //寄存器间接调用
                if(left == TY_REG){
                    if(tks[0] < KW_R8){
                        //2. call 通用寄存器
                        opcode = 0x41ff;
                        writeBytes(opcode,2);
                        //写入寄存器索引
                        writeBytes(0xd0 + modrm->reg,1);
                    }else{
                        //3. call r8-r15寄存器
                        opcode = 0xffd0 + modrm->reg;
                        writeBytes(opcode,2);
                    }
                }
                break;
            }
            case KW_JMP:{
                if(is_rel){
                    //1. 内部符号 eb
                    opcode = 0xeb;
                }else{
                    //2. 外部符号 e9 00 00 00 00
                    opcode = 0xe9;
                }
                writeBytes(opcode,1);
                break;
            }
            default:{
                writeBytes(opcode >> 8,1);
                writeBytes(opcode,1);
            }
        }
        int rel  = inst->imm - (asmer::curAddr + 4);//调用符号地址相对于下一条指令地址的偏移，因此加4
        //存在外部引用
        if(is_rel){
            //构建4字节 0
            writeBytes(0x00000000,4);
        }
        writeBytes(rel,4);
    }
    else if(type == KW_INT)
    {
        writeBytes(opcode,1);
        writeBytes(inst->imm,1);
    }
    else if(type == KW_PUSH)
    {
        //1. 立即数 push
        if(left == TY_IMMED)
        {
            //强制使用32位立即数进行存储
            opcode = 0x68;
            writeBytes(opcode,1);
            writeBytes(inst->imm,4);
        }
        else if(tks[0] < KW_R8)
        {
            opcode +=(unsigned char)(modrm->reg);
            writeBytes(opcode,1);
        }else{
            //要加个0x41 前缀指令
            writeBytes(0x41,1);
            opcode +=(unsigned char)(modrm->reg);
            writeBytes(opcode,1);
        }
    }
    //TODO : supoort inc instruct
    //TODO : supoort dec instruct
    //TODO : supoort neg instruct
    else if(type == KW_INC || type == KW_DEC || type == KW_NEG )
    {
        std::cout << "not support instruct:" << type << std::endl;
        assert(false);
    }
    else if(type == KW_POP)
    {
        opcode += (unsigned char)(modrm->reg);
        writeBytes(opcode,1);
    }
    else if(type == KW_MUL || type == KW_DIV)
    {
        writeBytes(opcode,1);
        if(type == KW_MUL)
            exchar = 0xe8;
        else
            exchar = 0xf8;
        exchar += (unsigned char)(modrm->reg);
        writeBytes(exchar,1);
    }
}

void Instruct::gen0Op() {
    unsigned char opcode = i_0opcode[0];
    writeBytes(opcode,1);
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
