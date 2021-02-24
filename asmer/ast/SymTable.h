/**
 *@ClassName SymTable
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/18 0018 上午 10:25
 *@Version 1.0
 **/
#ifndef COLANG_SYMTABLE_H
#define COLANG_SYMTABLE_H

#include <iostream>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "Sym.h"

namespace asmer{
    //符号表
    class SymTable
    {

    public:
        //符号声明列表
        std::unordered_map<std::string,Sym*> symbolTable;
        //记录有序的符号数据定义
        std::vector<Sym*>                    data_symbol;

    public:
        //检查符号是否存在
        bool hasName(std::string name);
        //添加符号
        void addSym (Sym* sym);
        //获取已经定义的符号
        Sym* getSym (std::string name);
        //切换下一个段，由于一般只有.text和.data，因此可以此时创建段表项目
        void switchSeg(std::string segname);
        //导出所有的符号到elf
        void exportSyms();
        //注销所有空间
        ~SymTable();
    };
};
#endif //COLANG_SYMTABLE_H
