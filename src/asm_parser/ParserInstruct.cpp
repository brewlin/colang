/**
 *@ClassName ParserInstruct
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 5:11
 *@Version 1.0
 **/

#include "Parser.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Token.h"
#include "Utils.h"

namespace asmer{
    Instruct* Parser::parseInstruct() {
        //当前token 必须是指令
        assert(scanner->token() >= KW_PUSH && scanner->token() <= KW_RET);

        Token token = scanner->token();

        //解析两个参数的指令
        if( token >= KW_MOV && token <= KW_LEA )  return parseTwoInstruct();
        //解析1个参数的指令
        if( token >= KW_CALL && token <= KW_POP ) return parseOneInstruct();
        //解析0个参数的指令
        if(token == KW_RET)                       return parseZeroInstruct();

        parse_err("[Parser] unknow instruct:%s\n",scanner->value());
    }
    Instruct* Parser::parseTwoInstruct() {
        assert(scanner->token() >= KW_MOV && scanner->token() <= KW_LEA );
        //构建一条指令数据
        Instruct * inst = new Instruct(scanner->token());

        std::string name;;
        Sym* sym;

        //next one;
        switch(scanner->scan())
        {
            //立即数 $
            case TK_IMMED:
                //get number;
                assert(scanner->scan() == TK_NUMBER);
                //保存立即数
                inst->inst->imm32 = std::stoi(scanner->value());
                break;
            case ident://立即数
                type=immd;
                name+=id;
                lr=table.getlb(name);
                instr.imm32=lr->addr;
                //处理数据段重定位项
                if(scanLop==2)//第二次扫描记录重定位项
                {
                    if(!lr->isEqu)//不是equ
                    {
                        //记录符号
                        relLb=lr;
                    }
                }
                break;
            case lbrac://内存寻址
                type=memr;
                BACK
                mem();
                break;
            case subs://负立即数
                type=immd;
                match(number);
                instr.imm32=-num;
                break;
            default://寄存器操作数 11 rm=des reg=src
                type=regs;
                BACK
                    len=reg();
                if(regNum!=0)//双reg，将原来reg写入rm作为目的操作数，本次写入reg
                {
                    modrm.mod=3;//双寄存器模式
                    modrm.rm=modrm.reg;//因为统一采用opcode rm,r 的指令格式，比如mov rm32,r32就使用0x89,若是使用opcode r,rm 形式则不需要
                    modrm.reg=token-br_al-(1-len%4)*8;//计算寄存器的编码
                }
                else//第一次出现reg，临时在reg中，若双reg这次是目的寄存器，需要交换位置
                {
                    modrm.reg=token-br_al-(1-len%4)*8;//计算寄存器的编码
                }
                regNum++;
        }

    }
    Instruct* Parser::parseOneInstruct() {
        //构建一条指令数据
        Instruct * inst = new Instruct;
    }
    Instruct* Parser::parseZeroInstruct() {
        //构建一条指令数据
        Instruct * inst = new Instruct;
    }
};