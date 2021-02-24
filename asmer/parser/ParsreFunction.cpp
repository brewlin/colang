/**
 *@ClassName ParsreFunction
 *@Author brewlin
 *@Date 2020/12/15 0015 下午 5:23
 *@Version 1.0
 **/
#include "Parser.h"
#include "asmer/ast/Function.h"
#include "Utils.h"

namespace asmer
{

    /**
     * 解析函数区域的所有指令
     * @param labelname
     */
    Function* Parser::parseFunction(std::string labelname) {
        //这里可能是函数的开头
        //也可能是函数某一部分的标签，例如if，else这些默认会生成标签
        assert(scanner->token() >= KW_MOV && scanner->token() <= KW_RET);

        //将标签保存起来
        Function* func = new Function(labelname);

        //解析当前标签(函数)下所有的指令 并保存到function中
        Instruct* inst;
        do{

            Token token = scanner->token();

            //解析两个参数的指令
            if( token >= KW_MOV && token <= KW_LEA )
                inst  = parseTwoInstruct();
            //解析1个参数的指令
            else if( token >= KW_CALL && token <= KW_POP )
                inst  = parseOneInstruct();
            //解析0个参数的指令
            else if(token == KW_RET)
                inst  = parseZeroInstruct();
            else
                parse_err("[Parser] unknow instruct:%s\n",scanner->value());

            func->instructs.push_back(inst);
        //当前token 必须是指令
        }while(scanner->token() >= KW_MOV && scanner->token() <= KW_RET);

        return func;
    }

};