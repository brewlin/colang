/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef CO_LANG_RUNTIME_H
#define CO_LANG_RUNTIME_H
#include "Context.h"
#include "Expression.h"

class Package;
/**
 * 运行时
 */
class Runtime : public Context
{
public:
    explicit        Runtime() = default;
    void            addStatement(Statement* stmt);
    std::vector<Statement*> getStatements();

    //全局函数表 操作
    void       addFunc(const std::string& name,Function* f);
    bool       hasFunc(const std::string& name,bool is_extern = false);
    Function*  getFunc(const std::string& name,bool is_extern = false);

    //结构体操作
    void       addStruct(const std::string& name,Struct* f);
    bool       hasStruct(const std::string& name);
    Struct*    getStruct(const std::string& name);
public:
    //存储结构体定义
    std::unordered_map<std::string,Struct*>    structs;
    //全局变量
    std::unordered_map<std::string,VarExpr*> gvars;

    //顺序存储函数表 for irgen bin
    std::vector<Function*> order_funcs;
    //存储全局函数
    std::unordered_map<std::string,Function*>  funcs;
    std::unordered_map<std::string,Function*>  extern_funcs;
    //存储全局所有的待执行语句
    std::vector<Statement*>       stmts;
    //保存全局 静态字符串
    std::vector<StringExpr*>      strs;
    //每个包下面保存所有的函数
    std::unordered_map<std::string,Package*>   packages;

};

#endif //CO_LANG_RUNTIME_H
