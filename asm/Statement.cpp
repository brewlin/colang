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
    Value cond = this->cond->asmgen(rt,ctx);

    Interpreter::enterContext(ctx);
    //判断条件是否为真
    while(cond.cast<bool>()){
        //内层循环不断执行 while语句块
        //外层用于判断 条件是否继续为true
        for(auto& stmt : block->stmts){
//            std::cout << stmt->toString() <<std::endl;
            ret = stmt->asmgen(rt,ctx);
            if(ret.execType == ExecReturn){
                goto outside;

            }else if(ret.execType == ExecBreak){
                //这里表示可能有多长循环 如果内部break 不能影响到外部的执行
                //所以在返回到外层循环时 恢复到 normal状态 因为外层还需要继续执行
                ret.execType = ExecNormal;
                goto outside;
            }else if(ret.execType == ExecContinue)
            {
                //模拟continue 中断下面的指令继续执行
                ret.execType = ExecNormal;
                break;
            }
        }
        //继续检查条件是否成立
        cond = this->cond->asmgen(rt,ctx);
        if(!cond.isType<Bool>())
            panic(
                    "TypeError: expects bool type in while condition at line %d, "
                    "col %d\n",
                    line, column);
    }
    outside:
    Interpreter::leaveContext(ctx);
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