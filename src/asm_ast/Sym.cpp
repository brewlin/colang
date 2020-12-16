/**
 *@ClassName Sym
 *@Author brewlin
 *@Date 2020/12/14 0014 下午 3:26
 *@Version 1.0
 **/
#include "Sym.h"
#include "Asmer.h"
#include "src/asm_parser/Parser.h
#include "ElfFile.h"
#include "asmer.h"

asmer::SymTable symtable;

namespace asmer
{
    //对于重定位文件是0，链接后开始于0x08048100
    int Sym::curAddr = 0x00000000;

    /**
     * 创建一个符号
     * @param name
     * @param externed
     */
    Sym::Sym(std::string name, bool externed):
    name(name),
    externed(externed)
    {
        //初始化当前符号偏移量
        addr = curAddr;
        //TODO: 初始化当前符号所在的段名
        segName = ".text";
        //当前符号默认长度为0
        len = 0;
        if(externed){
            //如果是外部链接 不存在当前符号偏移量,段名也是未知
            addr = 0;
            segName = "";
        }

    }
    /**
     * 数字定义
     * @param name
     * @param len
     */
    Sym::Sym(std::string name, int len) {
        addr     = curAddr;
        segName  = ".data";
        len      = len;
        externed = false;
        curAddr  += len;
    }
    void Sym::write() {
        //TODO:
        Asmer::write(value,len);
    }
    Sym::~Sym() {

    }


    int SymTable::hasName(std::string name) {
        return symbolTable.find(name) != symbolTable.end();
    }
    void SymTable::addSym(asmer::Sym *sym) {
        //只在第一遍添加符号
        if(scanLop != 1){
            delete  sym;
            return;
        }
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

    }
    /**
     * 静态字符串定义
     * @param name
     * @param str
     */
    Sym::Sym(std::string name, std::string str):
    name(name)
    {
        addr     = curAddr;
        segName  = ".data";
        len      = str.size();
        externed = false;
        curAddr  += str.size();
    }
    void Sym::write() {
        //TODO:
        Asmer::write(value,len);
    }
    Sym::~Sym() {

    }


    int SymTable::hasName(std::string name) {
        return symbolTable.find(name) != symbolTable.end();
    }
    void SymTable::addSym(asmer::Sym *sym) {
        //只在第一遍添加符号
        if(scanLop != 1){
            delete  sym;
            return;
        }
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
            order_symbol->push_back(sym);
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
        if(scanLop == 1)
        {
            //地址对齐
            dataLen += (4 - dataLen % 4 ) % 4;
            //新建一个段
            obj.addShdr(curSeg,Sym::curAddr);
            if(curSeg != ".bss")
                dataLen += Sym::curAddr;
        }
        //切换下一个段名
        curSeg = segname;
        //清0段偏移
        Sym::curAddr = 0;
    }
    /**
     * 导出所有段符号
     */
    void SymTable::exportSyms() {
        for(auto it : symbolTable){
            Sym* sym = it.second;
            obj.addSym(sym);
        }
    }
    void SymTable::write()
    {
        for(auto sym : order_symbol){
            sym->write();
        }
        //只输出定义符号
        std::cout << "------------定义符号------------" << std::endl;
        if(showAss)
            for(auto sym : order_symbol)
                std::cout << sym->name << std::endl;
    }
    SymTable::~SymTable() {

    }


};