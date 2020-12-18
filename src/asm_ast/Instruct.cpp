/**
 *@ClassName Instruct
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 4:35
 *@Version 1.0
 **/
#include "Instruct.h"
#include <iostream>
#include <string>
#include "Token.h"

namespace asmer{

//ModRM,SIB,Inst结构
    ModRM::ModRM():mod(-1),reg(0),rm(0){}
    SIB::SIB()    :scale(-1),index(0),base(0){}
    Inst::Inst()  :opcode(0),disp(0),dispLen(0),imm32(0){}

    Instruct::Instruct(Token type)
    {
        is_rel     = false;
        is_func    = false;
        this->type = type;
        left       = TY_INVAL;
        right      = TY_INVAL;
        regnum     = 0;
    }
    //设置disp，自动检测disp长度（符号），及时是无符号地址值也无妨
    void Inst::setDisp(int d,int len)
    {
        dispLen = len;
        disp = d;
    }
    //按照记录的disp长度输出
    void Inst::writeDisp()
    {
        if(dispLen)
        {
            Instruct::writeBytes(disp,dispLen);
            dispLen = 0;//还原
        }
    }
};