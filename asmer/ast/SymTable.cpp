/**
 *@ClassName SymTable
 *@Deacription go
 *@Author brewlin
 *@Date 2020/12/18 0018 上午 10:25
 *@Version 1.0
 **/
#include "SymTable.h"
#include "Asmer.h"

namespace asmer{

    bool SymTable::hasName(std::string name) {
        return symbolTable.find(name) != symbolTable.end();
    }
    void SymTable::addSym(asmer::Sym *sym) {
        //之前符号可能已经被定义过了，且是全局的
        if(symbolTable.count(sym->name)){
            Sym* pre_sym = symbolTable[sym->name];
            if(pre_sym->global)
                sym->global = true;
        }
        symbolTable[sym->name] = sym;
        //保存数据
        if(sym->segName == ".data"){
            data_symbol.push_back(sym);
        }

    }
    /**
     * @param name
     * @return
     */
    Sym* SymTable::getSym(std::string name) {
        if(hasName(name)){
            return symbolTable[name];
        }else{
            //获取诸葛符号的时候没有定义，默认先创建一个外部符号添加到全局符号表中
            symbolTable[name] = new Sym(name,true);
            return symbolTable[name];
        }
    }
    SymTable::~SymTable() {

    }
};