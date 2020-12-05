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
    //每个包下面保存所有的函数
    std::unordered_map<std::string,Package*>   packages;
};

extern Runtime* rt;
#endif //CO_LANG_RUNTIME_H
