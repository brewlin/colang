/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Context.h"


/**
 * 是否存在该变量
 * @param varname
 * @return
 */
bool Context::hasVar(const std::string &varname)
{
    return vars.count(varname) == 1;

}
/**
 * 添加变量
 * @param varname
 * @param value
 */
void Context::createVar(const std::string &varname,VarExpr* ident)
{
    vars.emplace(varname,ident);
}
/**
 * 获取变量
 * @param varname
 * @return
 */
VarExpr* Context::getVar(const std::string &varname)
{
    if(auto res = vars.find(varname) ; res != vars.end())
        return res->second;
    return nullptr;
}


