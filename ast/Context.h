/*
 * @author brewlin
 * @date   2020/9/6
 */
#ifndef LANG_CONTEXT_H
#define LANG_CONTEXT_H

#include "Value.h"
#include <string>
#include <map>


/**
 * 上下文
 */
class Context{
public:
    explicit Context() = default;

    //全局变量表 操作
    bool       hasVar(const std::string& identname);
    void       createVar(const std::string& identname,IdentExpr* ident);
    IdentExpr* getVar(const std::string& identname);

public:
    //保存了作用域内的变量
    std::unordered_map<std::string,IdentExpr*> vars;
    //标记变量是否是 函数参数
    std::map<std::string, bool> isFuncArg;

public:
    std::string cur_funcname;
    //处于循环 或者某个 block块内，生成汇编需要找到终止的索引label
    std::string end_str;
    std::string start_str;
    int         point;

};
#endif //LANG_CONTEXT_H
