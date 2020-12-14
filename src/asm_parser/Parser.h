#ifndef CO_LANG_ASMER_PARSER_H
#define CO_LANG_ASMER_PARSER_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "Token.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "Scanner.h"


namespace asmer {
    
class Parser {
public:
    asmer::Scanner* scanner;

public:
    explicit Parser(const std::string filepath);
    ~Parser();
    std::string printToken();
    void parse();
};

};


#endif //CO_LANG_PARSER_H
