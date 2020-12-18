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
        //本地符号覆盖外部符号
        if(hasName(sym->name)){
            //如果本地保存的为外部符号，且新增的这个为本地符号 说明可以覆盖了
            if(symbolTable[sym->name]->externed == true && sym->externed == false){
                //删除之前保存的
                delete symbolTable[sym->name];
                symbolTable[sym->name] = sym;
            }
            //符号不存在
        }else{
            symbolTable[sym->name] = sym;
        }

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

    /**
     * 切换下一个段，由于一般只有.text和.data，因此可以此时创建段表项目
     * 当前段名
     * @param segname
     */
    void SymTable::switchSeg(std::string segname) {
        //地址对齐
        dataLen += (4 - dataLen % 4 ) % 4;
        dataLen += asmer::curAddr;
        //切换下一个段名
//        curSeg = segname;
    }
    /**
     * 导出所有段符号
     */
    void SymTable::exportSyms()
    {
        for(auto it : symbolTable)
        {
            Sym* sym = it.second;
            Asmer::elf->addSym(sym);
        }
    }
    SymTable::~SymTable() {

    }
};