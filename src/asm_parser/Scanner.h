#ifndef CO_LANG_ASMER_SCANNER_H
#define CO_LANG_ASMER_SCANNER_H

#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "src/asm_ast/Token.h"

using namespace std;

namespace asmer
{
    
class Scanner {
public:
    explicit Scanner(const std::string filepath);
    ~Scanner();
    std::string printToken();

    std::fstream fs;
    std::unordered_map<std::string,Token > keywords;
    std::tuple<Token ,std::string>         currentToken;

    Token           token()const;
    std::string     value()const;
    Token           scan();
private:
    char            next();
    char            peek();

    std::tuple <Token ,std::string> _scan();
    std::tuple <Token ,std::string> parseNumber(char first);
    std::tuple <Token ,std::string> parseString(char c);
    std::tuple <Token ,std::string> parseKeyword(char c);


public:
    //记录当前词法分析行|列
    int line = 1;
    int column = 0;

};

};
#endif