/**
 *@ClassName Interpreter
 *@Author brewlin
 *@Date 2020/9/3 0003 下午 3:38
 *@Version 1.0
 **/
#ifndef LANG_INTERPRETER_H
#define LANG_INTERPRETER_H

#include "do.h"
#include "Ast.h"
#include "Parser.h"
#include "Context.h"
#include "Value.h"

class Interpreter{
public:
    explicit Interpreter(const std::string& filename);
    ~Interpreter();

public:
    void execute();

public:
    static void enterContext(std::deque<Context*> ctx);
    static void leaveContext(std::deque<Context*> ctx);
    static Value assignSwitch(Token opt,Value lhs,Value rhs);
    static Value callFunction(Runtime* rt,Function* f,
                           std::deque<Context*> prevCtxChain,
                           std::vector<Expression*> args);
    static Value calcBinaryExpr(Value lhs,Token opt,Value rhs,
                                    int line,int column);
    static Value calcUnaryExpr(Value& lhs,Token opt,
                                    int line,int column);

private:
    void parseCommandOption(int argc,char* argv){}

private:
    std::deque<Context*> ctx;
    Runtime* rt;
    Parser* p;
};

#endif //LANG_INTERPRETER_H
