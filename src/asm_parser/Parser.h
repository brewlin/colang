#ifndef CO_LANG_ASMER_PARSER_H
#define CO_LANG_ASMER_PARSER_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "src/asm_ast/Token.h"
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
    void parseKeyword();
    void parseLabel();
    void parseInstruct();
};

};

//记录扫描的次数，第一遍扫描计算所有符号的地址或者值，第二编扫描，生成指令的二进制内容
extern int scanLop;
//有效数据长度
extern int dataLen;

#endif //CO_LANG_PARSER_H
