#include "Parser.h"
#include "Utils.h"

int scanLop = 1;
//有效数据长度
int dataLen = 0;

namespace asmer{

Parser::Parser(const std::string filepath)
{
    scanner = new Scanner(filepath);
    symtable = new SymTable();

    std::string fullname = filepath.substr(filepath.find_last_of('/')+1);
    filename = fullname.substr(0,fullname.size() - 2);
    outname  = filename + ".o";
}
Parser::~Parser()
{
    delete scanner;
}

/**
 * 解析
 * @param rt
 */
void Parser::parse()
{
    scanner->scan();
    if(scanner->token() == TK_EOF) return;

    do{
        //能走到最外层 一般只有 .text .data  .global 已经标签声明
        switch(scanner->token()){
            //解析段声明
            case KW_DATA:
            case KW_TEXT:{
                symtable->switchSeg(scanner->value());
                //next
                scanner->scan();
                continue;
            }
            case KW_GLOBAL: parseGlobal(); continue;
            case KW_LABEL : parseLabel();  continue;
            case TK_EOF:                   break;
            default:
                parse_err("[Paser] unknow instruct:%s\n",scanner->value());
        }
    }while(scanner->token() != TK_EOF);
}

/**
 *
 * @return
 */
std::string Parser::printToken()
{
    auto  tk = scanner->scan();
    auto  str = scanner->value();
    while(tk != TK_EOF){
        std::cout << "" << tk << " => " << str << "\n";
        tk = scanner->scan();
    }

}

};
