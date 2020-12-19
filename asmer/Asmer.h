/**
 *@ClassName Asmer
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:34
 *@Version 1.0
 **/
#ifndef COLANG_ASMER_H
#define COLANG_ASMER_H

#include <iostream>
#include <string>

#include "src/asm_parser/Parser.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Token.h"
#include "ElfFile.h"

using namespace asmer;

class Asmer
{
public:
    Parser*     parser;
    FILE*       out;
public:
    static ElfFile*    elf;
    static Asmer*      obj;
    //实时统计写入的字节数
    static int         bytes;
    static int         data;
    static int         text;
public:
    Asmer(std::string filename);
    ~Asmer();
    //解析
    void execute();
    //构建
    void buildElf();
    //生成
    void writeElf();
    //更新代码段中的引用
    void updateText();
    void updateTextFunc(asmer::Function* func);
    //数据段中暂不支持引用
    //指令生成
    void InstGen();
    //在构建elf文件的时候主要是计算偏移量，不进行指令翻译
    void InstUpdate();
    void InstUpdate0p(Instruct* inst);
    void InstUpdate1p(Instruct* inst);
    void InstUpdate2p(Instruct* inst);
    //写入
    static void writeBytes(void* b, int len);
    static void expand(int len);
};

//
extern ElfFile* elf;

#endif //COLANG_ASMER_H
