/**
 *@ClassName CompilerFunc
 *@Author brewlin
 *@Date 2020/9/27 0027 下午 3:25
 *@Version 1.0
 **/
#include "Compiler.h"

void Compiler::registerFunc(){
    for (auto* f : rt->order_funcs){
        declarationFunc(rt,ctx,f);
    }
}
//创建上下文 准备执行函数
void Compiler::enterContext(std::deque<Context *> &ctx, llvm::BasicBlock *block)
{
    auto* temp = new Context(block);
    ctx.push_back(temp);
}
//离开上下文
void Compiler::leaveContext(std::deque<Context *> &ctx)
{
    auto* tempContext = ctx.back();
    ctx.pop_back();
    delete tempContext;
}

void Compiler::registerDefaultMain()
{
    //这里 用于注册生成一个main函数 在ld 链接的时候可以直接执行
    std::vector<llvm::Type*> sysArgs;
    llvm::FunctionType* mainFuncType = llvm::FunctionType::get(llvm::Type::getVoidTy(rt->llvmContext), makeArrayRef(sysArgs), false);
    llvm::Function* mainFunc = llvm::Function::Create(mainFuncType, llvm::GlobalValue::ExternalLinkage, "main",rt->llvmModule.get());
    llvm::BasicBlock* block = llvm::BasicBlock::Create(rt->llvmContext, "entry",mainFunc);
    rt->builder.SetInsertPoint(block);
    //将当前block入栈
    enterContext(ctx,block);

    auto stmts = rt->getStatements();
    //顺序执行语句
    for(auto stmt : stmts){
        std::string stmtstr = stmt->toString();
        Debug("%s",stmtstr.c_str());
        //执行表达式语句
//        stmt->interpret(rt,ctx);
        stmt->irgen(rt,ctx);
//        stmt->interpret(rt,ctx);
    }
    rt->builder.CreateRet(ctx.back()->returnValue);
    leaveContext(ctx);
}

/**
 * 返回一个函数指针
 * @param f
 * @return
 */
PointerT Compiler::getFuncPtr(Runtime* rt,Function *f)
{
    std::vector<llvm::Type*> argTypes;
    //这里就是搞清楚所有参数的类型
    for(auto &arg: f->params){
        //TODO:函数申明时形参由于我们是动态语言，目前不知道如果动态，先固定为void*型把
        argTypes.push_back(getVarType(rt,"void*"));
    }
    llvm::Type* retType = nullptr;
    retType = getVarType(rt,"void*");
    //下面就是定义函数体了
    llvm::FunctionType* functionType = llvm::FunctionType::get(retType, argTypes, false);

    return llvm::PointerType::get(functionType, 0);
}
/**
 *
 * @param rt
 * @param ctx
 * @param f
 */
void Compiler::declarationFunc(Runtime* rt,std::deque<Context*> ctx,Function* f){
    std::string funcname(f->name);
    if(f->isObj){
        funcname = f->structname + "::"+f->name;
    }
    Debug("register func:%s",funcname.c_str());
    //判断是否已经注册过，
    llvm::Function * calleeF = rt->llvmModule->getFunction(funcname);
    if(calleeF)
        Debug("Funcation already register :%s" ,funcname.c_str());
    //这里对实参进行求值
    //在fucallExpr 中只有内置函数才会求值，自定义函数在这里求值
    Debug("Create function declaration of :%s " ,funcname.c_str());
    std::vector<llvm::Type*> argTypes;
    //这里就是搞清楚所有参数的类型
    for(auto &arg: f->params){
        //TODO:函数申明时形参由于我们是动态语言，目前不知道如果动态，先固定为int型把
        argTypes.push_back(getVarType(rt,"string"));
    }
    llvm::Type* retType = nullptr;
    //TODO:函数返回值类型 目前默认为 int吧
    retType = getVarType(rt,"int");

    //下面就是定义函数体了
    llvm::FunctionType* functionType = llvm::FunctionType::get(retType, argTypes, false);
    llvm::Function* function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, funcname, rt->llvmModule.get());
    rt->funcTypes[funcname] = function;

    //申明函数不需要创建 函数体
    if( f->block ){
        llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(rt->llvmContext, "entry", function, nullptr);

        rt->builder.SetInsertPoint(basicBlock);
        //接下来的blcok都是在当前函数块内申明 语句
        enterContext(ctx,basicBlock);

        int i = 0;
        for(auto &ir_arg_it: function->args()){
            std::string paramname = f->params[i];
            //获取函数形参名
            ir_arg_it.setName(paramname);
            llvm::Value* argAlloc;
            //TODO:参数可能是一个指针
            //        if( (*origin_arg)->type->isArray )
            //            argAlloc = context.rt->builder.CreateAlloca(PointerType::get(context.typeSystem.getVarType(rt,(*origin_arg)->type->name), 0));
            //        else
            //TODO: 动态类型实现 这里其实是去定义一个变量，我们就手动定义了

            argAlloc = setVar(rt,ctx,paramname,"string");
            rt->builder.CreateStore(&ir_arg_it, argAlloc, false);
            //存储一份本地变量
            ctx.back()->locals[paramname] = argAlloc;
            //存储该变量的类型
            ctx.back()->types[paramname] = "string";
            ctx.back()->isFuncArg[paramname] = true;
            i++;
        }
        //接下来就是注册 block块
        for(auto& stmt : f->block->stmts){
            //TODO: 处理返回值
            stmt->irgen(rt,ctx);
        }
        llvm::Value* retv = ctx.back()->returnValue;
        if( retv) rt->builder.CreateRet(retv);
        else return panic("Function block return value not founded");

        leaveContext(ctx);
    }
}
