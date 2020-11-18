/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Runtime.h"
/**
 * 初始化runtime 全局相关
 * 注册内置函数
 */
Runtime::Runtime():builder(llvmContext) {}
Runtime::Runtime(const std::string &name):builder(llvmContext)
{
    llvmModule = std::unique_ptr<llvm::Module>(new llvm::Module(name,llvmContext));
}
std::vector<Statement*> Runtime::getStatements()
{
    return stmts;
}
void Runtime::addStatement(Statement* stmt)
{
    stmts.push_back(stmt);
}
