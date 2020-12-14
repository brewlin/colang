#include "Parser.h"
#include "Utils.h"

int scanLop = 1;
//有效数据长度
int dataLen = 0;

namespace asmer{

Parser::Parser(const std::string filepath)
{
    scanner = new Scanner(filepath);
}
Parser::~Parser()
{
    delete scanner;
}

/**
 * @param rt
 */
void Parser::parse()
{
    scanner->scan();
    if(scanner->token() == TK_EOF) return;

    do{
        asmer::Token tk = scanner->token();
        //解析指令 mov,push je jmp call ...等
        if(tk >= KW_PUSH && tk <= KW_JE){
            parseInstruct();
            continue;
        }
        //解析全局关键字，如全局数据定义
        if(tk == TK_DOT || (tk >= KW_COMM && tk <= KW_LABEL)){
            parseKeyword();
            continue;
        }

        parse_err("unknow instruct:%s\n",scanner->value());
    }while(scanner->token() != TK_EOF);
}

std::string Parser::printToken()
{
    auto  tk = scanner->scan();
    while(std::get<0>(tk) != TK_EOF){
        std::cout << "" << std::get<0>(tk) << " => " << std::get<1>(tk) << "\n";
        tk = scanner->scan();
    }

}

};
