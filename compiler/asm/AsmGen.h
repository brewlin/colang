/**
 *@ClassName AsmGen
 *@Author brewlin
 *@Date 2020/10/10 0010 下午 3:58
 *@Version 1.0
 **/
#ifndef COMPILER_ASMGEN_H
#define COMPILER_ASMGEN_H

#include "Expression.h"
#include "Context.h"
#include "Value.h"
#include "Parser.h"


class AsmGen {
    std::deque<Context*> ctx;

public:
    static const char* argreg8[] ;
    static const char* argreg16[];
    static const char* argreg32[];
    static const char* argreg64[];

public:
    //用于生产全局唯一变量
    static int count;

    explicit AsmGen(const std::string& filename);
    ~AsmGen();
    void execute();
    void link();

public:
    //为局部变量 计算栈偏移量
    static void writeln(const char *fmt, ...);
    static void enterContext(std::deque<Context *> &ctx);
    static void leaveContext(std::deque<Context *> ctx);

    static void assign_offsets(Function* fn);
    static void funcs_offsets();
    static void funcs_offsets(Function* fn);
    static void classs_offsets();
    static void registerMain();
    static void registerStrings();
    static void registerVars();
    //创建全局string
    static void CreateGlobalString(StringExpr* expr);

    static void registerFuncs();
    static void registerFunc(Function* fn);
    static void CreateFunction(Function* fn,Class* c = nullptr);
    static void registerObjects();
    static void registerObjectFuncs(Class* c);
    //寄存器相关
    static void Store_gp(int r, int offset, int sz);
    static void Store();
    static void GenAddr(VarExpr* var);
    static void Load();
    static void CreateCmp();
    static void Push();
    static void PushS(const char* arg);
    static void Pop(const char* arg);
    static int  Push_arg(deque<Context *> prevCtxChain,Function* func,FunCallExpr* fce);
    static void Pop_arg(std::vector<Expression *> &args);

    //current function
    static Function*      currentFunc;
    static std::ofstream* out;
    static Parser*        parser;
};



//6个寄存器用于保存函数参数，多的就存放在栈上
#define GP_MAX 6
#define FP_MAX 8

#endif //COMPILER_ASMGEN_H
