/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Statement.h"
#include "Utils.h"
#include "Compiler.h"
/**
 * if 控制语句执行
 */
llvm::Value* IfStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    Debug("Create if statement");
    //对判断条件的表达式求值
    llvm::Value* condValue = this->cond->irgen(rt,ctx);
    if( !condValue )
        return nullptr;
    condValue = Compiler::castToBoolean(rt,condValue);
    llvm::Function* theFunction = rt->builder.GetInsertBlock()->getParent();
    // the function where if statement is in
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(rt->llvmContext, "then", theFunction);
    llvm::BasicBlock *falseBB = llvm::BasicBlock::Create(rt->llvmContext, "else");
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(rt->llvmContext, "ifcont");

    //如果有else block
    if( this->elseBlock ){
        rt->builder.CreateCondBr(condValue, thenBB, falseBB);
    } else{
        rt->builder.CreateCondBr(condValue, thenBB, mergeBB);
    }
    rt->builder.SetInsertPoint(thenBB);
    //将if 的block入栈，表示新的局部变量
    Compiler::enterContext(ctx,thenBB);
    //解析所有的 true的block 插入当前block
    //TODO:Block 也该抽象为 express 方便进行递归
    for(auto& stmt : block->stmts){
        stmt->irgen(rt,ctx);
    }
    Compiler::leaveContext(ctx);

    //开始解析else的block块
    thenBB = rt->builder.GetInsertBlock();
    if( thenBB->getTerminator() == nullptr ){       //
        rt->builder.CreateBr(mergeBB);
    }

    if( this->elseBlock ){
        theFunction->getBasicBlockList().push_back(falseBB);    //
        rt->builder.SetInsertPoint(falseBB);            //

        Compiler::enterContext(ctx,thenBB);
        //TODO:block 也该抽象为else表达式
        for(auto& elseStmt : elseBlock->stmts) {
            Debug("%s",elseStmt->toString().c_str());
            elseStmt->irgen(rt,ctx);
        }
        Compiler::leaveContext(ctx);
        rt->builder.CreateBr(mergeBB);
    }

    theFunction->getBasicBlockList().push_back(mergeBB);        //
    rt->builder.SetInsertPoint(mergeBB);        //
    //TODO: 需要支持 else if 关键字
    return nullptr;
}
/**
 * 执行while 语句 该函数可能会递归调用因为存在多个嵌套while循环
 * @param rt
 */
llvm::Value* WhileStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    llvm::Function* theFunction = rt->builder.GetInsertBlock()->getParent();

    //创建两个基本快 一个是条件 一个 语句
    llvm::BasicBlock *block = llvm::BasicBlock::Create(rt->llvmContext, "whileloop", theFunction);
    llvm::BasicBlock *after = llvm::BasicBlock::Create(rt->llvmContext, "whilecount");

    //初始化
//    if( this->initial )
//        this->initial->irgen(context);

    llvm::Value* condValue = this->cond->irgen(rt,ctx);
    if( !condValue )
        return nullptr;
    condValue = Compiler::castToBoolean(rt,condValue);
    Debug("condition:%s",Compiler::getTypeStr(condValue).c_str());
//    condValue = Compiler::binaryOper(rt,TK_NE,condValue,boolean);
    // 创建一个跳转
    rt->builder.CreateCondBr(condValue, block, after);
    rt->builder.SetInsertPoint(block);
    //插入 block
    Compiler::enterContext(ctx,block);
    for(auto& stmt : this->block->stmts) {
        Debug("%s",stmt->toString().c_str());
        stmt->irgen(rt,ctx);
    }
    Compiler::leaveContext(ctx);
    //TODO: for 循环是需要 每次循环做些收尾操作而我们的while不存在 所以不需要
//    if( this->increment ){
//        this->increment->irgen(context);
//    }
    // execute the again or stop
    condValue = this->cond->irgen(rt,ctx);
    condValue = Compiler::castToBoolean(rt,condValue);
    //继续创建一个跳转
    rt->builder.CreateCondBr(condValue, block, after);

    // insert the after block
    theFunction->getBasicBlockList().push_back(after);
    rt->builder.SetInsertPoint(after);
    return nullptr;
}
/**
 * 表达式 语句
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* ExpressionStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{

    Debug("%s",expr->toString().c_str());
    //对表达式求值
    return this->expr->irgen(rt,ctx);
}
llvm::Value* ReturnStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    Debug("Create return statement");
    llvm::Value* returnValue = this->ret->irgen(rt,ctx);
    //return说明存在某个block块中  {}
    ctx.back()->returnValue = returnValue;
    return returnValue;
}
/**
 * TODO:break语句
 */
llvm::Value* BreakStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    return nullptr;
}
/**
 * TODO:continue 语句
 */
llvm::Value* ContinueStmt::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    return nullptr;
}