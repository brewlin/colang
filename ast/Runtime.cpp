/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Runtime.h"
#include "Parser.h"
std::vector<Statement*> Runtime::getStatements()
{
    return stmts;
}
void Runtime::addStatement(Statement* stmt)
{
    stmts.push_back(stmt);
}


/**
 * 添加一个函数
 * @param name
 * @param f
 */
void Runtime::addFunc(const std::string &name, Function *f)
{
    order_funcs.push_back(f);

    //函数名是 包名 + 函数名
    std::string realfuncname = f->parser->getpkgname() + "." + name;
    if(f->isExtern)
        extern_funcs.insert(std::make_pair(realfuncname,f));
    else
        funcs.insert(std::make_pair(realfuncname,f));
}
/**
 * 检查是否存在该函数
 * @param name
 * @return
 */
bool Runtime::hasFunc(const std::string &name, bool is_extern)
{
    if(is_extern)
        return extern_funcs.count(name) == 1;
    else
        return funcs.count(name) == 1;
}
/**
 * 获取一个func
 * @param name
 * @return
 */
Function* Runtime::getFunc(const std::string &name, bool is_extern)
{
    if(is_extern){
        if(auto f = extern_funcs.find(name);f != funcs.end())
            return f->second;
    }else{
        if(auto f = funcs.find(name);f != funcs.end())
            return f->second;
    }
    return nullptr;
}


/**
 * 添加一个结构体
 * @param name
 * @param f
 */
void Runtime::addStruct(const std::string &name, Struct *f)
{
    structs.insert(std::make_pair(name,f));
}
/**
 * 检查是否存在该结构体
 * @param name
 * @return
 */
bool Runtime::hasStruct(const std::string &name)
{
    return structs.count(name) == 1;
}
/**
 * 获取一个Struct
 * @param name
 * @return
 */
Struct* Runtime::getStruct(const std::string &name)
{
    if(auto f = structs.find(name);f != structs.end())
        return f->second;
    return nullptr;
}
