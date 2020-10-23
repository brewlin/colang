/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_CONTEXT_H
#define LANG_CONTEXT_H

#include "Value.h"
#include "Llvm.h"
#include <string>


/**
 * 上下文
 */
class Context{
public:
    explicit Context();
    explicit Context(llvm::BasicBlock *block);
    virtual  ~Context();

    //全局变量表 操作
    bool      hasVar(const std::string& identname);
    void      createVar(const std::string& identname,Value value);
    Variable* getVar(const std::string& identname);
    //全局函数表 操作
    void      addFunc(const std::string& name,Function* f);
    bool      hasFunc(const std::string& name);
    Function* getFunc(const std::string& name);
    //结构体操作
    void      addStruct(const std::string& name,Struct* f);
    bool      hasStruct(const std::string& name);
    Struct*   getStruct(const std::string& name);

private:
    std::unordered_map<std::string,Variable*> vars;
    //TODO:compiler save baiscblock
    //解释器相关的参数
public:
    std::unordered_map<std::string,Function*> funcs;
    //存储结构体定义
    std::unordered_map<std::string,Struct*>   structs;


    //编译器相关参数
public:

    //结构体定义
    std::map<std::string, llvm::StructType*> structTypes;
    std::map<std::string, llvm::Function*>   funcTypes;
    //这个是 llvm用于表示的block块
    llvm::BasicBlock * block;
    //这个用于  llvm 表示 该块的返回值
    llvm::Value *returnValue;
    //用于表示该块的 局部变量
    std::map<std::string, llvm::Value*> locals;
    // 变量的类型名: a => double
    std::map<std::string, std::string> types;
    //顺序存储函数表 for compiler bin
    std::vector<Function*> order_funcs;
    //标记变量是否是 函数参数
    std::map<std::string, bool> isFuncArg;

    //asmgen 相关
public:
    //处于循环时的context 需要设置
    std::string end_str;
    std::string start_str;
    int         point;

};
#endif //LANG_CONTEXT_H
