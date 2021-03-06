#ifndef CO_LANG_ASMER_PARSER_H
#define CO_LANG_ASMER_PARSER_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "asmer/ast/Token.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "Scanner.h"
#include "asmer/ast/Function.h"
//#include "asmer/ast/Instruct.h"
#include "asmer/ast/Sym.h"
#include "asmer/ast/SymTable.h"
#include "asmer/elf/ElfFile.h"

namespace asmer {

class Instruct;
class Parser {
public:
    //文件解析扫描
    asmer::Scanner*        scanner;
    //全局 data段里的各种符号
    asmer::SymTable*       symtable;
    //elf文件
    ElfFile*               elf;
    //全局 text段里的各种指令
    std::vector<Function*> funcs;
    std::string            filepath;
    std::string            filename;
    std::string            outname;
    //data段的空间大小 data段不需要二次扫描，在parser阶段确定大小和偏移量
    int                    data_size;
    //text段指令大小
    int                    text_size;
    //操作指令需要扫描两次，修正所有的label偏移量
    bool                   ready;
public:
    explicit Parser(const std::string filepath,ElfFile* elf);
    ~Parser();
    std::string printToken();
    void parse();
    void parseLex();
    void genInst();
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
