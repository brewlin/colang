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


namespace asmer{
    

static unsigned char i_2opcode[]=
    {
//			8位操作数			 |		32位操作数
//r,r  r,rm|rm,r r,im|r,r  r,rm|rm,r r,im
        0x88,0x8a,0x88,0xb0,0x89,0x8b,0x89,0xb8,//mov
        0x38,0x3a,0x38,0x80,0x39,0x3b,0x39,0x81,//cmp
        0x28,0x2a,0x28,0x80,0x29,0x2b,0x29,0x81,//sub
        0x00,0x02,0x00,0x80,0x01,0x03,0x01,0x81,//add
        0x00,0x00,0x00,0x00,0x00,0x8d,0x00,0x00//lea
    };
static unsigned short int i_1opcode[]=
    {
        0xe8,0xcd,/*0xfe,*/0xf7,0xf7,0xf7,0x40,0x48,0xe9,//call,int,imul,idiv,neg,inc,dec,jmp<rel32>
        0x0f84,0x0f8f,0x0f8c,0x0f8d,0x0f8e,0x0f85,0x0f86,//je,jg,jl,jge,jle,jne,jna<rel32>
        //0xeb,//jmp rel8
        //0x74,0x7f,0x7c,0x7d,0x7e,0x75,0x76,//je,jg,jl,jge,jle,jne,jna<rel8>
        /*0x68,*/0x50,//push
        0x58//pop
    };
static unsigned char i_0opcode[]=
    {
        0xc3//ret
    };
int inLen = 0;
/*
	输出ModRM字节
	mod(2)|reg(3)|rm(3)
*/
void Instruct::writeModRM() {
    if(modrm->mod!=-1)//有效
    {
        unsigned char mrm=(unsigned char)(((modrm->mod&0x00000003)<<6)+((modrm->reg&0x0000007)<<3)+(modrm->rm&0x00000007));
        writeBytes(mrm,1);
        //printf("输出ModRM=0x%08x\n",mrm);
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

    asmer::curAddr += len;//计算地址
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
        flag=true;
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
    // cout<<"disp32="<<inst.disp32<<",disp8="<<(int)inst.disp8<<"(<-"<<inst.disptype<<":(0-disp8;1-disp32) imm32="<<inst->imm32<<endl;
    //计算操作码索引 (mov,8,reg,reg)=000 (mov,8,reg,mem)=001 (mov,8,mem,reg)=010 (mov,8,reg,imm)=011
    //(mov,32,reg,reg)=100 (mov,32,reg,mem)=101 (mov,32,mem,reg)=110 (mov,32,reg,imm)=111  [0-7]*(i_lea-i_mov)
    int index = -1;
    //立即数都是8字节
    int len   = 8;
    if(left == TY_IMMED)//鉴别操作数种类
        index = 3;
    else
        index = (right -2) * 2 + left - 2;
    index = (type - KW_MOV ) * 8+ ( 1 - 8 % 8)* 8 + index;//附加指令名称和长度
    unsigned char opcode = i_2opcode[index];
    unsigned char exchar;
    switch(modrm->mod)
    {
        case -1://reg,imm
            switch(type)
            {
                case KW_MOV://b0+rb MOV r/m8,imm8 b8+rd MOV r/m32,imm32
                    opcode += (unsigned char)(modrm->reg);
                    writeBytes(opcode,1);
                    break;
                case KW_CMP://80 /7 ib CMP r/m8,imm8 81 /7 id CMP r/m32,imm32
                    writeBytes(opcode,1);
                    exchar = 0xf8;
                    exchar += (unsigned char)(modrm->reg);
                    writeBytes(exchar,1);
                    break;
                case KW_ADD://80 /0 ib ADD r/m8, imm8 81 /0 id ADD r/m32, imm32
                    writeBytes(opcode,1);
                    exchar = 0xc0;
                    exchar += ( unsigned char )(modrm->reg);
                    writeBytes(exchar,1);
                    break;
                case KW_SUB://80 /5 ib SUB r/m8, imm8 81 /5 id SUB r/m32, imm32
                    writeBytes(opcode,1);
                    exchar = 0xe8;
                    exchar += ( unsigned char)(modrm->reg);
                    writeBytes(exchar,1);
                    break;
            }
            //可能的重定位位置 mov eax,@buffer,也有可能是mov eax,@buffer_len，就不许要重定位，因为是宏
            updateRel();
            writeBytes(inst->imm32,len);//一定要按照长度输出立即数
            break;
        case 0://[reg],reg reg,[reg]
            writeBytes(opcode,1);
            writeModRM();
            if(modrm->rm == 5)//[disp32]
            {
                updateRel();//可能是mov eax,[@buffer],后边disp8和disp32不会出现类似情况
                inst->writeDisp();//地址肯定是4字节长度
            }
            else if(modrm->rm == 4)//SIB
            {
                writeSIB();
            }
            break;
        case 1://[reg+disp8],reg reg,[reg+disp8]
            writeBytes(opcode,1);
            writeModRM();
            if(modrm->rm == 4)
                writeSIB();
            inst->writeDisp();
            break;
        case 2://[reg+disp32],reg reg,[reg+disp32]
            writeBytes(opcode,1);
            writeModRM();
            if(modrm->rm == 4)
                writeSIB();
            inst->writeDisp();
            break;
        case 3://reg,reg
            writeBytes(opcode,1);
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
        //统一使用长地址跳转，短跳转不好定位
        if(type == KW_CALL  || type == KW_JMP)
            writeBytes(opcode,1);
        else
        {
            writeBytes(opcode >> 8,1);
            writeBytes(opcode,1);
        }
        int rel  = inst->imm32 - (asmer::curAddr + 4);//调用符号地址相对于下一条指令地址的偏移，因此加4
        bool ret = updateRel();//处理可能的相对重定位信息，call fun,如果fun是本地定义的函数就不会重定位了
        if(ret)//相对重定位成功，说明之前计算的偏移错误
            rel = -4;//对于链接器必须的初始值
        writeBytes(rel,4);
    }
    else if(type == KW_INT)
    {
        writeBytes(opcode,1);
        writeBytes(inst->imm32,1);
    }
    else if(type == KW_PUSH)
    {
        if(left == TY_IMMED)
        {
            opcode = 0x68;
            writeBytes(opcode,1);
            writeBytes(inst->imm32,4);
        }
        else
        {
            opcode +=(unsigned char)(modrm->reg);
            writeBytes(opcode,1);
        }
    }
    else if(type == KW_INC)
    {
        opcode+=(unsigned char)(modrm->reg);
        writeBytes(opcode,1);
    }
    else if(type == KW_DEC)
    {
        opcode += (unsigned char)(modrm->reg);
        writeBytes(opcode,1);
    }
    else if(type == KW_NEG)
    {
        exchar=0xd8;
        exchar+=(unsigned char)(modrm->reg);
        writeBytes(opcode,1);
        writeBytes(exchar,1);
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
