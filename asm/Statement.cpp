/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Statement.h"
#include "Utils.h"
#include "Interpreter.h"
#include "AsmGen.h"
/**
 * if 控制语句执行
 * @param rt
 * @param ctx
 * @return
 */
ExecResult IfStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{
    ExecResult ret(ExecNormal);
    int c = AsmGen::count ++;
    //对判断条件的表达式求值
    Value cond = this->cond->asmgen(rt,ctx);
    AsmGen::CreateCmp(cond.type);
    AsmGen::writeln("  je  .L.else.%d", c);

    AsmGen::enterContext(ctx);

    //顺序执行所有的 block 语句
    for(auto& stmt : block->stmts){
//            std::cout << stmt->toString() <<std::endl;
        ret = stmt->asmgen(rt,ctx);
        if(ret.execType == ExecReturn)
            break;
        else if(ret.execType == ExecBreak)
            break;
        else if(ret.execType == ExecContinue)
            break;
    }
    AsmGen::leaveContext(ctx);
    AsmGen::writeln("  jmp .L.end.%d", c);
    AsmGen::writeln(".L.else.%d:", c);

    if(elseBlock != nullptr){
        AsmGen::enterContext(ctx);
        //执行 else 里的语句块
        for(auto& elseStmt : elseBlock->stmts){
//                std::cout << elseStmt->toString() <<std::endl;
            ret =  elseStmt->asmgen(rt,ctx);
            if(ret.execType == ExecReturn)
                break;
            else if(ret.execType == ExecBreak)
                break;
            else if(ret.execType == ExecContinue)
                break;
        }
        //离开上下文
        AsmGen::leaveContext(ctx);
    }
    AsmGen::writeln(".L.end.%d:", c);


    return ret;
}
/**
 * 执行while 语句 该函数可能会递归调用因为存在多个嵌套while循环
 * @param rt
 * @param ctx
 * @return
 */
ExecResult WhileStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{
    ExecResult ret;



    int c = AsmGen::count ++;
    //表示循环开始的 标签：
    AsmGen::writeln(".L.begin.%d:", c);
    //对判断条件的表达式求值
    Value cond = this->cond->asmgen(rt,ctx);
    AsmGen::CreateCmp(cond.type);
    AsmGen::writeln("  je  .L.while.end.%d", c);

    AsmGen::enterContext(ctx);
    //设置当前ctx 所处的 count计数  用于定位标签
    ctx.back()->break_point = c;
    ctx.back()->break_str   = ".L.while.end";
    //内层循环不断执行 while语句块
    //外层用于判断 条件是否继续为true
    for(auto& stmt : block->stmts){
//            std::cout << stmt->toString() <<std::endl;
        ret = stmt->asmgen(rt,ctx);
    }
    AsmGen::leaveContext(ctx);

    AsmGen::writeln("  jmp .L.begin.%d",c);
    AsmGen::writeln(".L.while.end.%d:", c);
    return ret;
}
/**
 * 表达式 语句
 * @param rt
 * @param ctx
 * @return
 */
ExecResult ExpressionStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{

//    std::cout << expr->toString() <<std::endl;
    //对表达式求值
    this->expr->asmgen(rt,ctx);
    return ExecResult(ExecNormal);
}
/**
 * 求值并且返回值 如: return 3+2;
 * value = 3+2
 * return execresult(return,5)
 * @param rt
 * @param ctx
 * @return
 */
ExecResult ReturnStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{
    Value retVal = this->ret->asmgen(rt,ctx);
    return ExecResult(ExecReturn,retVal);
}
/**
 * break语句
 * @param rt
 * @param ctx
 * @return
 */
ExecResult BreakStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{
    //判断当前是否处在循环中
    Context* c = ctx.back();
    if(c->break_point && !c->break_str.empty()){
        AsmGen::writeln("  jmp %s.%d",c->break_str.c_str(),c->break_point);
    }
    return ExecResult(ExecBreak);
}
/**
 * continue 语句
 * @param rt
 * @param ctx
 * @return
 */
ExecResult ContinueStmt::asmgen(Runtime *rt, std::deque<Context *> ctx)
{
    return ExecResult(ExecContinue);
}