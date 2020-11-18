/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_RUNTIME_H
#define LANG_RUNTIME_H
#include "Context.h"
#include "Expression.h"
/**
 * 运行时
 */
class Runtime : public Context
{
public:
    explicit        Runtime();
    explicit        Runtime(const std::string& name);
    void            addStatement(Statement* stmt);
    std::vector<Statement*> getStatements();

public:
    //存储全局所有的待执行语句
    std::vector<Statement*>       stmts;
    //保存全局 静态字符串
    std::vector<StringExpr*>      strs;

    llvm::LLVMContext             llvmContext;
    llvm::IRBuilder<>             builder;
    std::unique_ptr<llvm::Module> llvmModule;
};

#endif //LANG_RUNTIME_H
