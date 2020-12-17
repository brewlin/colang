/**
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:07
 *@Version 1.0
 **/
#ifndef COLANG_ASMER_SYM_H
#define COLANG_ASMER_SYM_H

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


namespace asmer{

    extern int  curAddr;
    extern int  dataLen;

    //符号记录
    struct Sym
    {
        //一个段内符号的偏移累加量
        //段名，如: .text .data .bass 当前64位没有显示指定 会自动判断
        std::string segName;
        //符号名
        std::string name;
        //是否是外部符号，true的时候表示为外部的，此时curAddr不累加
        bool        externed;
        //符号段偏移
        int         addr;
        //符号字节长度 db-1 d2-2 dd-4 xword-8
        int         len;
        std::string str;
        Sym(std::string name,bool externed);
        Sym(std::string name,int len);
        Sym(std::string name,std::string str);
        ~Sym();
    };

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
        void write();
        //注销所有空间
        ~SymTable();
    };

};
extern asmer::SymTable symtable;
#endif //COLANG_SYM_H
