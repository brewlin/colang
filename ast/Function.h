/**
 *@Author brewlin
 *@Date 2020/9/22 0022 下午 3:26
 *@Version 1.0
 **/
#ifndef COMPILER_FUNCTION_H
#define COMPILER_FUNCTION_H
#include <string>

struct Expression;
/**
 * 函数
 */
struct Function{
    //函数定义 函数声明  外部函数
    explicit Function():isExtern(false),isObj(false){};
    ~Function(){delete block;}

    std::string name;
    bool        isExtern;
    bool        isObj;
    std::string structname;
    std::string rettype;

    //保存函数块内的本地变量 for asm gen offset
    std::vector<Expression*> locals;
    std::vector<Expression*> params_var;
    //表示该函数所需要的栈空间 一般是本地变量的总和
    int                      stack_size;

    std::vector<std::string> params;
    Block* block{};
    Expression* retExpr{};
};

#endif //COMPILER_FUNCTION_H
