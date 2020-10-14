/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Runtime.h"
#include "Builtin.h"
/**
 * 初始化runtime 全局相关
 * 注册内置函数
 */
Runtime::Runtime():builder(llvmContext)
{
    builtin["print"] = &do_print;
    builtin["println"] = &do_println;
    builtin["typeof"] = &do_typeof;
    builtin["input"] = &do_input;
    builtin["length"] = &do_len;
    builtin["time"] = &do_time;
}
Runtime::Runtime(const std::string &name):builder(llvmContext)
{
    llvmModule = std::unique_ptr<llvm::Module>(new llvm::Module(name,llvmContext));
}
bool Runtime::hasBuiltinFunc(const std::string &name)
{
    return builtin.count(name) == 1;
}
std::vector<Statement*> Runtime::getStatements()
{
    return stmts;
}
Runtime::BuiltinFuncType Runtime::getBuiltinFunc(const std::string &name)
{
    if (auto res = builtin.find(name); res != builtin.end()) {
        return res->second;
    }
    return builtin[name];
}
void Runtime::addStatement(Statement* stmt)
{
    stmts.push_back(stmt);
}
