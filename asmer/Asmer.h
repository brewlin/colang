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

#include "src/asm_parser/Parer.h"
#include "src/asm_ast/Function.h"
#include "src/asm_ast/Instruct.h"
#include "src/asm_ast/Token.h"

using namespace asmer;

class Asmer
{
    Parser* paser;
public:
    Asmer(std::string filename);
    ~Asmer();
    void write(int value,int len);
    void execute();
    //更新代码段中的引用
    void updateText();
    void updateTextFunc(asmer::Function* func);
    //数据段中暂不支持引用
    
    //指令生成
    void InstGen();



};

#endif //COLANG_ASMER_H
