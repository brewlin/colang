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
struct VarExpr;
struct ClosureExpr;
class Parser;
using namespace std;
/**
 * 函数
 */
struct Function{
    //函数定义 函数声明  外部函数
    explicit Function()
    :isExtern(false),isObj(false),parser(nullptr),is_variadic(false){};
    ~Function(){delete block;}

    string name;
    bool   isExtern;
    bool   isObj;
    string structname;
    string rettype;

    //parser
    Parser* parser;

    //保存函数块内的本地变量 for asm gen offset
    unordered_map<string,VarExpr*> locals;
    //这里保存两份加快查找 因为函数参数在计算栈偏移量的时候和顺序有关
    unordered_map<string,VarExpr*> params_var;
    vector<VarExpr*>                    params_order_var;
    //这里表示当前函数参数有可变参数，需要进行可变参数传参
    bool                                is_variadic;
    int                                 size;
    int                                 stack;
    int                                 l_stack;
    int                                 g_stack;
    //表示该函数所需要的栈空间 一般是本地变量的总和
    int                      stack_size;
    //支持内嵌闭包函数，在codgen阶段会为所有的闭包函数生成随机签名
    vector<Function*>        closures;
    static int               closureidx;
    //每个闭包函数默认会被替换为一个ClosureExpression，在签名生成成功后会一并修改执行的VarExpression
    ClosureExpr*             receiver;

    vector<string> params;
    Block* block{};
    Expression* retExpr{};

    VarExpr* getVar(string name);
};

#endif //COMPILER_FUNCTION_H
