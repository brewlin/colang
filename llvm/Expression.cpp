/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Expression.h"
#include "Compiler.h"
#include "Log.h"

//===---------------------------------------------------------------------===//
// 计算所有的表达式 并返回一个 Value 结构，

//用0表示一个 nullptr
llvm::Value* NullExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(rt->llvmContext), 0, true);
}
llvm::Value* BoolExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(rt->llvmContext), this->literal, true);
}
//字面值
llvm::Value* CharExpr::irgen(Runtime* rt, std::deque<Context*> ctx){

    return llvm::ConstantInt::get(llvm::Type::getInt8Ty(rt->llvmContext), this->literal, true);
}
//int类型
llvm::Value* IntExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(rt->llvmContext), this->literal, true);
}

llvm::Value* DoubleExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(rt->llvmContext), this->literal);
}

llvm::Value* StringExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
//    return ConstantPointerNull::get(llvm::Type::getInt8PtrTy(rt->llvmContext),this->literal);
    return rt->builder.CreateGlobalString(this->literal, "string");
}
/**
 * 数组变量生成
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* ArrayExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
//    std::vector<Value> elements;
    //数组内的元素可能类型不同 如 [1,"2","3"] 所以需要遍历生成Value 存入vector中
//    for(auto& e: this->literal)
        //遍历调用 interpret 生成 Value
//        elements.push_back(e->interpret(rt,ctx));
    return nullptr;
}
/**
 * 这里是获取变量
 * 这里的变量可能没有初始化 可能返回了一个空
 */
llvm::Value* VarExpr::irgen(Runtime* rt, std::deque<Context*> ctx){

    llvm::Value* value = Compiler::getVar(ctx,varname);
    if( !value ){
        parse_err("AsmError:use of undefined variable %s at line %d co %d\n",
          varname.c_str(),line,column);
        return nullptr;
    }
    if( value->getType()->isPointerTy() ){
        auto arrayPtr = rt->builder.CreateLoad(value, "arrayPtr");
        Debug("ptr type:%s",Compiler::getTypeStr(arrayPtr).c_str());
        if( arrayPtr->getType()->isArrayTy() ){
            Debug("(Array Type)");
//            arrayPtr->setAlignment(16);
            std::vector<llvm::Value*> indices;
            //初始化一个数组 并全部为0
            indices.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(rt->llvmContext), 0, false));
            auto ptr = rt->builder.CreateInBoundsGEP(value, indices, "arrayPtr");
            return ptr;
        }
    }
    return value;
//    return rt->builder.CreateLoad(value, false, "");
}
/**
 * 索引 数组
 * @param rt a[1]
 * @param ctx
 * @return
 */
llvm::Value* IndexExpr::irgen(Runtime* rt, std::deque<Context*> ctx) {
    return nullptr;
}


/**
 * 赋值运算符 求值
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* AssignExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    /**
     * 1. 查看变量是否存在
     * 2. 对右边进行递归 irgen
     * 2. 不存在则先创建变量
     * 3. 对变量进行赋值
     */
    std::string lhsname;
    Debug("Create assignment of %s = ",lhsname.c_str());
    llvm::Value* dst;
    llvm::Value* exp;

    if(typeid(*lhs) == typeid(VarExpr))
    {
        lhsname = dynamic_cast<VarExpr*>(lhs)->varname;
        dst = Compiler::getVar(ctx,lhsname);
        //先求值，用于判断类型 这里对右边子树进行递归求值
        exp = rhs->irgen(rt,ctx);
        //这里可能会发现该变量没有定义
        //因为我们是动态类型所以这里需要主动注册该变量
        //该变量第一次使用，需要定义变量名
        if( !dst){
            //如果是结构体的话
            ctx.back()->locals[lhsname] = exp;
            std::string typestr(Compiler::getTypeStr(exp));
            //如果是指针则无限解引用
            if(typestr.compare("pointer") == 0) {
                llvm::Value *vt = exp;
                while (typestr.compare("pointer") == 0) {
                    vt = rt->builder.CreateLoad(vt);
                    typestr = Compiler::getTypeStr(vt);
                }
                if (typestr.compare("struct") == 0)
                    typestr = vt->getType()->getStructName().str();
            }
            ctx.back()->types[lhsname] = typestr;
//            Compiler::declarationVar(rt,ctx,lhsname,exp);
//            dst = Compiler::getVar(ctx,lhsname);
            return exp;
        }
        //这里需要进行 lhs operate rhs 运算 左右和右边进行计算
        exp = Compiler::binaryOper(rt,ctx,opt,dst,exp);

    //成员变量赋值
    }else if(typeid(*lhs) == typeid(MemberExpr))
    {
        //lhs MemberExpr->irgen()
        dst = lhs->irgen(rt,ctx);
        exp = rhs->irgen(rt,ctx);
        exp = Compiler::binaryOper(rt,ctx,opt,dst,exp);
    }


    //这边表示可能需要进行类型转换
    //TODO: 在进行运算前需要保持类型一致 有问题
    //exp = Compiler::cast(exp, Compiler::getVarType(rt,dstTypeStr), Compiler::currentBlock());

    //进行变量赋值 变量赋值放到 binaryOper里面去完成
    //rt->builder.CreateStore(exp, dst);
    //返回当前变量的值
    return dst;
}


/**
 * 函数调用求值
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* FunCallExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
    Debug("Create method call of %s",funcname.c_str());
    llvm::Function * calleeF = rt->llvmModule->getFunction(this->funcname);
    if( !calleeF ){
        //判断ast函数表有没有该函数，因为可能没有来得及注册该函数
//        Function* f = std::rotate(std::begin(container), std::begin(), std::end(container))->getFunc(funcname);
        Function* f = rt->getFunc(funcname);
        if(!f)
            Error("Function name not found :%s from ast",funcname.c_str());
        Compiler::declarationFunc(rt,ctx,f);
        calleeF = rt->llvmModule->getFunction(this->funcname);
        if(!calleeF)
            Error("Function name not found :%s from llvm",funcname.c_str());
    }
    if( calleeF->arg_size() != this->args.size() ){
        string p("Function arguments size not match, calleeF=" + std::to_string(calleeF->size()) + ", this->arguments=" + std::to_string(this->args.size()));
        Debug("%s",p.c_str());
    }
    std::vector<llvm::Value*> argsv;
    //将ast里定义的value 参数 转换为 llvm::value
    for(auto it=this->args.begin(); it!=this->args.end(); it++){
        auto arg = *it;
        //args 里面存储的his expression* 表达式，所以需要求值后再存入
        llvm::Value* tm = arg->irgen(rt,ctx);
        Debug("call arg typeid(*it):%s type:%s",typeid(*arg).name(),Compiler::getTypeStr(tm).c_str());
        //结构体访问 需要解引用
        if(typeid(*arg) == typeid(MemberExpr)) {
            Debug("call arg find memberExpr");
            tm = rt->builder.CreateLoad(tm);
        }
        argsv.push_back(tm);
        if( !argsv.back() ){        // if any argument irgen(Runtime* rt, std::deque<Context*> ctx)fail
            return nullptr;
        }
    }
    //创建一个函数调用 IR
    return rt->builder.CreateCall(calleeF, argsv, "calltmp");
}
/**
 * 二元运算符求值
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* BinaryExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    llvm::Value* lhs = this->lhs ? this->lhs->irgen(rt,ctx) : nullptr;
    llvm::Value* rhs = this->rhs ? this->rhs->irgen(rt,ctx) : nullptr;

    Token  opt = this->opt;
    //lhs != null & rhs == null 一元求值
//    if(!lhs && rhs)
//        return calcUnaryExpr(lhs,opt,line,column);
    //二元求值
    return Compiler::binaryOper(rt,ctx,opt,lhs,rhs);
//    return calcBinaryExpr(lhs,opt,rhs,line,column);

}

/**
 * 针对结构体变量定义
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* NewExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    Debug("new expr got: type:%s",this->type.c_str());
    //获取struct 类型
    Struct* s = rt->getStruct(this->type);
    if(!s) return nullptr;

    llvm::Type* type = rt->structTypes[this->type];

    if(!type)return nullptr;
    //创建一个结构体变量
    llvm::Value* inst = rt->builder.CreateAlloca(type);
    //对指针求值 解引用
//    auto sp = rt->builder.CreateLoad(inst, "structPtr");

    //对象初始化，之前是初始化成员函数现在不需要了，TODO:可以做其他的
    //Compiler::initStruct(rt,inst,s);
    //需要初始化结构体的相关 成员函数
    return inst;
}
/**
 * struct p{
 *  v1
 *  v2
 *  func m(){}
 * }
 * 1. p.v1
 * 2. p.m()
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* MemberExpr::irgen(Runtime* rt, std::deque<Context*> ctx)
{
    Debug("got member expr varname:%s membername:%s",varname.c_str(),membername.c_str());
    return Compiler::getStructMember(rt,ctx,varname,membername);
}

/**
 * 函数调用求值
 * @param rt
 * @param ctx
 * @return
 */
llvm::Value* MemberCallExpr::irgen(Runtime* rt, std::deque<Context*> ctx){
    //method = structname::methodname
    std::string funcname = ctx.back()->types[varname] + "::"+membername;
    Debug("got member call expr varname:%s membername:%s funcname:%s",varname.c_str(),membername.c_str(),funcname.c_str());

    llvm::Function * calleeF = rt->llvmModule->getFunction(funcname);
    assert(calleeF != nullptr);
    if( calleeF->arg_size() != this->args.size() ){
        string p("Function arguments size not match, calleeF=" + std::to_string(calleeF->size()) + ", this->arguments=" + std::to_string(this->args.size())+"\n");
        Warn("%s",p.c_str());
    }
    std::vector<llvm::Value*> argsv;
    //将ast里定义的value 参数 转换为 llvm::value
    for(auto it=this->args.begin(); it!=this->args.end(); it++){
        //args 里面存储的his expression* 表达式，所以需要求值后再存入
        argsv.push_back((*it)->irgen(rt, ctx));
        if( !argsv.back() ){        // if any argument irgen(Runtime* rt, std::deque<Context*> ctx)fail
            return nullptr;
        }
    }
    //创建一个函数调用 IR
    return rt->builder.CreateCall(calleeF, argsv, "calltmp");
}

