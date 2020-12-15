/**
 *@ClassName ParsreFunction
 *@Author brewlin
 *@Date 2020/12/15 0015 下午 5:23
 *@Version 1.0
 **/
#include "Parser.h"
#include "src/asm_ast/Function.h"

namespace asmer
{

    /**
     * 解析函数区域的所有指令
     * @param labelname
     */
    Function* Parser::parseFunction(std::string labelname) {
        //当前token 必须是指令
        assert(scanner->token() >= KW_PUSH && scanner->token() <= KW_RET);

        //将标签保存起来
        Function* func = new Function(labelname);

        do{
            Instruct* inst = parseInstruct();
            func->instructs.push_back(inst);

        }(scanner->token() >= KW_PUSH && scanner->token() <= KW_RET);

    }

};