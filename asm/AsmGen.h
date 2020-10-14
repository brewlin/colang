/**
 *@ClassName AsmGen
 *@Author brewlin
 *@Date 2020/10/10 0010 下午 3:58
 *@Version 1.0
 **/
#ifndef COMPILER_ASMGEN_H
#define COMPILER_ASMGEN_H

#include "Expression.h"
#include "Runtime.h"
#include "Context.h"
#include "Value.h"
#include "Parser.h"

#define ALIGN_UP(x,a) (((x) + (a - 1)) & ~(a - 1))


class AsmGen {
    std::deque<Context*> ctx;
    Runtime* rt;
    Parser* p;
    //用于生产全局唯一变量
    static int count;

public:
    explicit AsmGen(const std::string& filename);
    ~AsmGen();
    void execute();
    //为局部变量 计算栈偏移量
    void assign_offsets();

public:
    static void writeln(const char *fmt, ...);

    void registerStrings();
    //创建全局string
    static void CreateGlobalString(StringExpr* expr);

    void registerFuncs();
    static void CreateFunction(Function* fn);

    //寄存器相关
    static void store_gp(int r, int offset, int sz);

};


#endif //COMPILER_ASMGEN_H
