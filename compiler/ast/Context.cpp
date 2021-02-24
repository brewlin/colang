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
VarExpr* Context::getVar(std::deque<Context*> ctx,const std::string& varname)
{
    //变量遍历表 看是否存在
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
        auto* ctx = *p;

        if(auto* var = ctx->getVar(varname);var != nullptr){
            return var;
        }
    }
    return nullptr;
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


