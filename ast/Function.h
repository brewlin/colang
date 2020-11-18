/**
 *@Author brewlin
 *@Date 2020/9/22 0022 下午 3:26
 *@Version 1.0
 **/
#ifndef COMPILER_FUNCTION_H
#define COMPILER_FUNCTION_H
#include <string>
#include <unordered_map>
#include <vector>
#include "Block.h"

struct Expression;
struct IdentExpr;
/**
 * 函数
 */
struct Function{
    //函数定义 函数声明  外部函数
    explicit Function():isExtern(false),isObj(false),is_multi(false){};
    ~Function(){delete block;}

    std::string name;
    bool        isExtern;
    bool        isObj;
    std::string structname;
    std::string rettype;

    //保存函数块内的本地变量 for asm gen offset
    std::unordered_map<std::string,IdentExpr*> locals;
    //这里保存两份加快查找 因为函数参数在计算栈偏移量的时候和顺序有关
    std::unordered_map<std::string,IdentExpr*> params_var;
    std::vector<IdentExpr*>                    params_order_var;
    //这里表示当前函数参数有可变参数，需要进行可变参数传参
    bool                                       is_multi;
    int                                        size;
    int                                        stack;
    int                                        l_stack;
    int                                        g_stack;
    //表示该函数所需要的栈空间 一般是本地变量的总和
    int                      stack_size;

    std::vector<std::string> params;
    Block* block{};
    Expression* retExpr{};
};

#endif //COMPILER_FUNCTION_H
