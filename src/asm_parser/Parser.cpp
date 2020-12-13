#include "Parser.h"

Parser::Parser(const std::string filepath):
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
}

std::string Parser::printToken()
{
    auto  tk = scanner->scan();
    while(std::get<0>(tk) != TK_EOF){
        std::cout << "" << getstd::get<0>(tk) << " => " << std::get<1>(tk) << "\n";
        tk = scanner->scan();
    }

}
