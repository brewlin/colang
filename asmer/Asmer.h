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

#include "parser/Parser.h"
#include "ast/Function.h"
#include "ast/Instruct.h"
#include "ast/Token.h"
#include "ElfFile.h"

using namespace asmer;

class Asmer
{
public:
    Parser*     parser;
    FILE*       out;
public:
    static ElfFile*    elf;
    //实时统计写入的字节数
    static int         bytes;
    static int         text;
    //data数据段总大小
    int         data;
public:
    Asmer(std::string filename);
    ~Asmer();
    //解析
    void execute();
    //构建
    void buildElf();
    //生成
    void writeElf();
    //指令收集
    void InstCollect();
    //在构建elf文件的时候主要是计算偏移量，不进行指令翻译
    void InstWrite();
    //写入
    void writeBytes(const void* b, int len);
};

#endif //COLANG_ASMER_H
