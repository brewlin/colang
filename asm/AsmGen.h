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

struct CoreValue{
    int     type;    //0

    int     interger; //4
    double  long_interger;//8
    char    cchar;//16
    char*   string;//17
    int     boolean;//25
};

class AsmGen {
    std::deque<Context*> ctx;
    Runtime* rt;
    Parser* p;

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
    //为局部变量 计算栈偏移量
    void assign_offsets();

public:
    static void writeln(const char *fmt, ...);
    static void enterContext(std::deque<Context *> &ctx);
    static void leaveContext(std::deque<Context *> ctx);

    void registerStrings();
    //创建全局string
    static void CreateGlobalString(StringExpr* expr);

    void registerFuncs();
    static void CreateFunction(Function* fn,Runtime* rt,std::deque<Context*> ctx);
    //寄存器相关
    static void Store_gp(int r, int offset, int sz);
    static void Store(ValueType type);
    static void GenAddr(IdentExpr* var);
    static void Load(ValueType     type);
    static void CreateCmp(ValueType type);
    static void Push();
    static void PushS(const char* arg);
    static void Pop(const char* arg);
    static int  Push_arg(Runtime *rt,std::deque<Context *> prevCtxChain,std::vector<Expression *> &args);
    static void Pop_arg(std::vector<Expression *> &args);

    //current function
    static Function* currentFunc;
};



//6个寄存器用于保存函数参数，多的就存放在栈上
#define GP_MAX 6
#define FP_MAX 8

#endif //COMPILER_ASMGEN_H
