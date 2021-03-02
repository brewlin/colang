/**
 *@ClassName ParserInstruct
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 5:11
 *@Version 1.0
 **/

#include "Parser.h"
#include "asmer/ast/Instruct.h"
#include "asmer/ast/Token.h"
#include "Utils.h"

namespace asmer{
    InstType Parser::parseInstruct(Instruct* inst) {
        std::string name;
        Sym* sym;
        //为了兼容 gnu 汇编 语法，这里做了很多兼容，目前支持的汇编指令如下
        /**
         * 1. 立即数
         *     mov $10,%rax     $开头的一定是立即数
         * 2. 重定位符号
         *     mov global_var(%rip),%rax   //全局变量寻址
         *     mov newobject@GOTPCREL(%rip), %rax  //全局函数寻址
         * 3. 内存访问
         *     mov -8(%rsp),$rax
         *     mov 8(%rsp),%rax
         *     mov (%rsp),%rax
         * 4. 寄存器访问
         *     mov %rsp,%ax,
         */

        inst->str += scanner->value() + " ";
        //判断每个指令
        switch(scanner->scan()) {
            //立即数 $ (正,负)
            //     mov $10,%rax     $开头的一定是立即数
            case TK_IMME:{
                unsigned long int  number   = 0;

                inst->str += scanner->value();
                //next one
                switch (scanner->scan()) {
                    //get number;
                    case TK_NUMBER:
                        number = std::stoul(scanner->value());
                        break;
                        //get -;
                    case TK_SUB:
                        //should be number
                        assert(scanner->scan() == TK_NUMBER);
                        number   = std::stoul(scanner->value());
                        number   = -number;
                        break;
                    default:
                        parse_err("[Parser] should be number at but got instruct:%s\n", scanner->value());
                }
                //保存立即数
                inst->inst->imm = number;
                inst->str += scanner->value();
                //next one
                scanner->scan();
                return TY_IMMED;
            }
            /*
             * 2. 重定位符号
             *     mov global_var(%rip),%rax   //全局变量寻址
             *     mov newobject@GOTPCREL(%rip), %rax  //全局函数寻址
             */
            case KW_LABEL:{
                //label name
                std::string name = scanner->value();
                //默认是本地引用
                inst->is_rel        = false;
                //next one
                inst->str += scanner->value();
                if(scanner->scan() == TK_AT){
                    //表明这是一个函数引用，需要进行相对地址定位
                    inst->is_func = true;
                    inst->is_rel  = true;
                    //next one shuould be GOTPCREL
                    inst->str += scanner->value();
                    assert(scanner->scan() == KW_LABEL);
                    //next one
                    inst->str += scanner->value();
                    scanner->scan();
                }
                //如果下面不是( 说明需要重定位
                if(scanner->token() == TK_LPAREN){
                    inst->is_rel  = true;
                    //接下来肯定解析的是 (%rip)
                    //shoulde be %rip
                    inst->str += scanner->value();
                    assert(scanner->scan() == KW_RIP);
                    //shoulde be )
                    inst->str += scanner->value();
                    assert(scanner->scan() == TK_RPAREN);

                    //next one
                    inst->str += scanner->value();
                    scanner->scan();
                }
                //其他情况 可能只是一个单独的标签调用，例如 jmp L.ELSE: 这种跳转

                //从符号表里查找看看是否已经定义了
                //计算没有定义也会返回一个 默认的 sym 并写入符号表中
                //TODO: 代码段中 有对符号的引用，需要后面计算是本地符号还是外部符号
                Sym* sym = symtable->getSym(name);
                //获得该符号的偏移量地址
                inst->inst->imm = sym->addr;
                inst->name = name;

                return TY_REL;
            }
            /**
             *
             * 3. 内存访问
             *    mov -8(%rsp),$rax
             *    mov 8(%rsp),%rax
             */
            case TK_SUB:
            case TK_NUMBER:{
                int num = 0;
                if(scanner->token() == TK_SUB){
                    inst->str += scanner->value();
                    assert(scanner->scan() == TK_NUMBER);
                    num -= std::atoi(scanner->value().c_str());
                }else{
                    num = std::atoi(scanner->value().c_str());
                }
                //获取寄存器
                inst->str += scanner->value();
                assert(scanner->scan() == TK_LPAREN);
                //可以是任意寄存器
                inst->str += scanner->value();
                scanner->scan();
                assert(scanner->token() >= KW_RAX && scanner->token() <= KW_RIP);
                //8位偏移量计算
                if( num >= -128 && num < 128)//disp8
                {
                    inst->modrm->mod = 1;
                    inst->inst->setDisp(num,1);
                //32为偏移量计算
                }else{
                    //mod: 1 0 
                    inst->modrm->mod = 2;
                    //填充32位数据，不够的需要补0
                    inst->inst->setDisp(num,4);
                }
                //索引
                inst->modrm->rm = scanner->token() - KW_RAX;
                //如果为rsp间接寻址就要特别一点
                //会额外多出sib指令段
                if( scanner->token() == KW_RSP)//sib
                {
                    inst->modrm->rm  = 4;//rm = 4 表示rsp的索引
                    inst->sib->scale = 0;//默认为0
                    inst->sib->index = 4;//index = 0b100 表示不存在该变址寄存器
                    inst->sib->base  = 4;//rsp 索引为4
                }
                //next one
                inst->str += scanner->value();
                assert(scanner->scan() == TK_RPAREN);
                inst->str += scanner->value();
                scanner->scan();
                return TY_MEM;

            }
            //mov (%rsp),%rax
            case TK_LPAREN:{
                //一般寄存器内存访问
                inst->str += scanner->value();
                switch(scanner->scan()){
                    case KW_RSP: {
                        //间接寻址 mod==0
                        inst->modrm->mod = 0;
                        inst->modrm->rm  = 4;//引导SIB
                        inst->sib->scale = 0;
                        inst->sib->index = 4;
                        inst->sib->base  = 4;
                        break;
                    }
                    case KW_RBP:{
                        //对于rbp的间接访问，需要当做偏移量访问
                        // mov (%rbp),%rax 实际是  mov 0(%rbp),%rax
                        inst->modrm->mod = 1;
                        inst->modrm->rm  = 5;
                        //所有需要补充1个0的偏移量字节
                        inst->inst->setDisp(0,1);
                        break;
                    }
                    //一般寄存器
                    default:{
                        inst->modrm->mod = 0;
                        inst->modrm->rm  = scanner->token() - KW_RAX - (1 - 8 % 8 ) * 8;
                    }
                }
                //eat )
                inst->str += scanner->value();
                assert(scanner->scan() == TK_RPAREN);
                //next one
                inst->str += scanner->value();
                scanner->scan();
                return TY_MEM;
            }
            case TK_MUL://* 号一般用于函数调用，例如 call *%r10
                //eat *
                inst->str += scanner->value();
               scanner->scan();
            default: {//寄存器操作数 11 rm=des reg=src
                //其他的默认为指令
                assert(scanner->token() >= KW_RAX && scanner->token() <= KW_RIP);
                inst->tks.push_back(scanner->token());

                if (inst->regnum)//双reg，将原来reg写入rm作为目的操作数，本次写入reg
                {
                    inst->modrm->mod = 3;//双寄存器模式
                    // inst->modrm->rm  = inst->modrm->reg;//因为统一采用opcode rm,r 的指令格式，比如mov rm32,r32就使用0x89,若是使用opcode r,rm 形式则不需要
                    inst->modrm->rm = scanner->token() - KW_RAX;//计算寄存器的编码
                } else//第一次出现reg，临时在reg中，若双reg这次是目的寄存器，需要交换位置
                {
                    //如果寄存器位 r8,r9,r10-r15 需要单独计算索引
                    if(scanner->token() >= KW_R8 && scanner->token() <= KW_R10){
                        inst->modrm->reg = scanner->token() - KW_R8;//计算寄存器的编码
                    }else{
                        inst->modrm->reg = scanner->token() - KW_RAX;//计算寄存器的编码
                    }
                }
                inst->regnum ++ ;

                //next one
                inst->str += scanner->value();
                scanner->scan();
                return TY_REG;
            }
        }
    }
    Instruct* Parser::parseTwoInstruct() {
        assert(scanner->token() >= KW_MOV && scanner->token() <= KW_LEA );
        //构建一条指令数据
        Instruct * inst = new Instruct(scanner->token(),this);
        inst->left      = parseInstruct(inst);
        //这里应该是逗号 ,
        assert(scanner->token() == TK_COMMA);
        //eat ,
        inst->right     = parseInstruct(inst);
        return inst;
    }
    Instruct* Parser::parseOneInstruct() {
        //构建一条指令数据
        Instruct * inst = new Instruct(scanner->token(),this);
        inst->left      = parseInstruct(inst);
        return inst;
    }
    Instruct* Parser::parseZeroInstruct() {
        //构建一条指令数据  like: ret
        Instruct * inst = new Instruct(scanner->token(),this);
        //eat ret
        inst->str = scanner->value();
        scanner->scan();
        return inst;
    }
};