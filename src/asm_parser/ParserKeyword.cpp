/**
 *@ClassName ParserKeyword
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 5:11
 *@Version 1.0
 **/

#include "Parser.h"
#include "src/asm_ast/Sym.h""

namespace asmer{
    void Parser::parseKeyword() {
        std::string label;

        //解析到了 .
        if(scanner->token() == TK_DOT){
            // += .
            label += scanner->value();
            //eat .
            scanner->scan();

            //解析段 .data .text
            if(scanner->token() == KW_DATA || scanner->token() == KW_TEXT){
                symtable->switchSeg(scanner->value());
                //next
                scanner->scan();
                return;
            }
            //解析 Label
            if(scanner->token() == KW_LABEL){
                parseLabel();
                return;
            }

        }


    }

    //解析label
    void Parser::parseLabel() {
        std::string labelname = scanner->value();
        //next;
        scanner->scan();
        // :
        assert(scanner->token() == TK_COLON);
        scanner->scan();

        //下面有两种可能
        /**
         * 1. label: 这个是一个函数定义
         * 2. label :数据类型定义
         *          .string
         */
         //stirng 数据定义
         if(scanner->token() == TK_DOT){
             //must .string
             scanner->scan();
             assert(scanner->token() == KW_STRING);

             //string value
             scanner->scan();
             assert(scanner->token() == TK_STRING);

             //将该全局字符串符号加入 符号表
             Sym* sym = new Sym(labelname,false);
             sym->str = scanner->value();
             symtable->addSym(sym);

             //next
             scanner->next();
             return;

         //普通标签定义 如 :函数名
         }else{
             Sym* sym = new Sym(labelname,false);
             symtable->addSym(sym);
//             当前返回让顶层继续解析
             return;

         }

    }
};
