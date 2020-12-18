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
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Sym.h"
#include "src/asm_ast/SymTable.h"


namespace asmer {

    
class Parser {
public:
    //文件解析扫描
    asmer::Scanner*        scanner;
    //全局 data段里的各种符号
    asmer::SymTable*       symtable;
    //全局 text段里的各种指令
    std::vector<Function*> funcs;
    std::string            filepath;
    std::string            filename;
    std::string            outname;

public:
    explicit Parser(const std::string filepath);
    ~Parser();
    std::string printToken();
    void parse();
    void parseKeyword();
    void parseGlobal();
    void parseQuad(std::string labelname);
    void parseString(std::string labelname);
    void parseLabel();

    InstType  parseInstruct(Instruct* inst);
    Instruct* parseZeroInstruct();
    Instruct* parseOneInstruct();
    Instruct* parseTwoInstruct();

    Function* parseFunction(std::string labelname);
};

};

//记录扫描的次数，第一遍扫描计算所有符号的地址或者值，第二编扫描，生成指令的二进制内容
extern int scanLop;
//有效数据长度
extern int dataLen;

#endif //CO_LANG_PARSER_H
