/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Context.h"


Context::Context() {}
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
void Context::createVar(const std::string &identname,IdentExpr* ident)
{
    vars.emplace(identname,ident);
}
/**
 * 获取变量
 * @param identname
 * @return
 */
IdentExpr* Context::getVar(const std::string &identname)
{
    if(auto res = vars.find(identname) ; res != vars.end())
        return res->second;
    return nullptr;
}


