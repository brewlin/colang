/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Context.h"


Context::Context():block(nullptr),returnValue(nullptr) {}
Context::Context(llvm::BasicBlock *block):block(block),returnValue(nullptr) {}
Context::~Context()
{
    for(auto v : vars)
        delete v.second;
}

/**
 * 是否存在该变量
 * @param identname
 * @return
 */
bool Context::hasVar(const std::string &identname)
{
    return vars.count(identname) == 1;

}
/**
 * 添加变量
 * @param identname
 * @param value
 */
void Context::createVar(const std::string &identname, Value value)
{
    auto* var  = new Variable;
    var->name  = identname;
    var->value = value;
    vars.emplace(identname,var);
}
/**
 * 获取变量
 * @param identname
 * @return
 */
Variable* Context::getVar(const std::string &identname)
{
    if(auto res = vars.find(identname) ; res != vars.end())
        return res->second;
    return nullptr;
}
/**
 * 添加一个函数
 * @param name
 * @param f
 */
void Context::addFunc(const std::string &name, Function *f)
{
    order_funcs.push_back(f);
    funcs.insert(std::make_pair(name,f));
}
/**
 * 检查是否存在该函数
 * @param name
 * @return
 */
bool Context::hasFunc(const std::string &name)
{
    return funcs.count(name) == 1;
}
/**
 * 获取一个func
 * @param name
 * @return
 */
Function* Context::getFunc(const std::string &name)
{
    if(auto f = funcs.find(name);f != funcs.end())
        return f->second;
    return nullptr;
}

/**
 * 添加一个结构体
 * @param name
 * @param f
 */
void Context::addStruct(const std::string &name, Struct *f)
{
    structs.insert(std::make_pair(name,f));
}
/**
 * 检查是否存在该结构体
 * @param name
 * @return
 */
bool Context::hasStruct(const std::string &name)
{
    return structs.count(name) == 1;
}
/**
 * 获取一个Struct
 * @param name
 * @return
 */
Struct* Context::getStruct(const std::string &name)
{
    if(auto f = structs.find(name);f != structs.end())
        return f->second;
    return nullptr;
}