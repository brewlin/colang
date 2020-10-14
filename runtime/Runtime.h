/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_RUNTIME_H
#define LANG_RUNTIME_H
#include "Context.h"
/**
 * 运行时
 */
class Runtime : public Context
{
    //定义一个函数指针
    using BuiltinFuncType = Value (*)(Runtime*,std::deque<Context*>,std::vector<Value>);
public:
    explicit        Runtime();
    explicit        Runtime(const std::string& name);
    bool            hasBuiltinFunc(const std::string& name);
    BuiltinFuncType getBuiltinFunc(const std::string& name);
    void            addStatement(Statement* stmt);
    std::vector<Statement*> getStatements();

private:

    std::unordered_map<std::string,BuiltinFuncType> builtin;
public:
    //存储全局所有的待执行语句
    std::vector<Statement*>       stmts;
    //保存全局 静态字符串
    std::vector<Expression*>      strs;

    llvm::LLVMContext             llvmContext;
    llvm::IRBuilder<>             builder;
    std::unique_ptr<llvm::Module> llvmModule;
};

#endif //LANG_RUNTIME_H
