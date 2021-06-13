/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Statement.h"
#include "Utils.h"
#include "asm/AsmGen.h"
#include "../internal/Internal.h"
#include "Block.h"
/**
 * if 控制语句执行
 * @param rt
 * @param ctx
 * @return
 */
void IfStmt::asmgen(std::deque<Context *> ctx)
{
    int c = AsmGen::count ++;
    //对判断条件的表达式求值
    this->cond->asmgen(ctx);
    //判断是否为true
    Internal::isTrue();

    AsmGen::CreateCmp();
    AsmGen::writeln("    je  L.else.%d", c);

    AsmGen::enterContext(ctx);

    //顺序执行所有的 block 语句
    for(auto& stmt : block->stmts){
//            std::cout << stmt->toString() <<std::endl;
        stmt->asmgen(ctx);
    }
    AsmGen::leaveContext(ctx);
    AsmGen::writeln("    jmp L.end.%d", c);
    AsmGen::writeln("L.else.%d:", c);

    if(elseBlock != nullptr){
        AsmGen::enterContext(ctx);
        //执行 else 里的语句块
        for(auto& elseStmt : elseBlock->stmts){
//                std::cout << elseStmt->toString() <<std::endl;
            elseStmt->asmgen(ctx);
        }
        //离开上下文
        AsmGen::leaveContext(ctx);
    }
    AsmGen::writeln("L.end.%d:", c);

}
void ForStmt::asmgen(std::deque<Context *> ctx)
{
}
/**
 * 执行while 语句 该函数可能会递归调用因为存在多个嵌套while循环
 * @param ctx
 * @return
 */
void WhileStmt::asmgen(std::deque<Context *> ctx)
{

    int c = AsmGen::count ++;
    //表示循环开始的 标签：
    AsmGen::writeln("L.while.begin.%d:", c);
    //对判断条件的表达式求值
    this->cond->asmgen(ctx);
    Internal::isTrue();
    AsmGen::CreateCmp();
    AsmGen::writeln("    je  L.while.end.%d", c);

    AsmGen::enterContext(ctx);
    //设置当前ctx 所处的 count计数  用于定位标签
    ctx.back()->point = c;
    ctx.back()->end_str   = "L.while.end";
    ctx.back()->start_str = "L.while.begin";
    //内层循环不断执行 while语句块
    //外层用于判断 条件是否继续为true
    for(auto& stmt : block->stmts){
//            std::cout << stmt->toString() <<std::endl;
        stmt->asmgen(ctx);
    }
    AsmGen::leaveContext(ctx);

    AsmGen::writeln("    jmp L.while.begin.%d",c);
    AsmGen::writeln("L.while.end.%d:", c);
}
/**
 * 表达式 语句
 * @param ctx
 * @return
 */
void ExpressionStmt::asmgen(std::deque<Context *> ctx)
{

//    std::cout << expr->toString() <<std::endl;
    //对表达式求值
    this->expr->asmgen(ctx);
}
/**
 * 求值并且返回值 如: return 3+2;
 * value = 3+2
 * return execresult(return,5)
 * @param ctx
 * @return
 */
void ReturnStmt::asmgen(std::deque<Context *> ctx)
{
    this->ret->asmgen(ctx);
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p) {
        //如果该变量不是 array 则抛出类型错误，不能对非数组变量进行索引操作
        std::string funcName = (*p)->cur_funcname;
        if (!funcName.empty())
            AsmGen::writeln("    jmp L.return.%s",funcName.c_str());
    }
}
/**
 * break语句
 * @param ctx
 * @return
 */
void BreakStmt::asmgen(std::deque<Context *> ctx)
{
    //判断当前是否处在循环中
//    Context* c = ctx.back();
//    if(c->point && !c->end_str.empty()){
//        AsmGen::writeln("    jmp %s.%d",c->end_str.c_str(),c->point);
//    }
    //可能要递归去查找当前是否处于循环中了
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p) {
        Context* c = *p;
        if(c->point && !c->end_str.empty()){
            AsmGen::writeln("    jmp %s.%d",c->end_str.c_str(),c->point);
        }
    }
}
/**
 * continue 语句
 * @param ctx
 * @return
 */
void ContinueStmt::asmgen(std::deque<Context *> ctx)
{
    //判断当前是否处在循环中
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p) {
        Context *c = *p;
//    Context* c = ctx.back();
        if (c->point && !c->start_str.empty()) {
            AsmGen::writeln("    jmp %s.%d", c->start_str.c_str(), c->point);
        }
    }
}