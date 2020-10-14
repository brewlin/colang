/**
 *@ClassName CompilerVar
 *@Author brewlin
 *@Date 2020/9/27 0027 下午 3:27
 *@Version 1.0
 **/

#include "Compiler.h"
static std::string typestr(llvm::Type* value);

/**
 *
 * @param rt
 * @param ctx
 * @param varname
 * @param stype
 * @return
 */
llvm::Value* Compiler::setVar(Runtime* rt,std::deque<Context *> &ctx, string varname, string stype) {
    Debug("Create var declaration of var:%s type:%s",varname.c_str(),stype.c_str());
    llvm::Type* type = Compiler::getVarType(rt,stype);
    llvm::Value* initial = nullptr;
    llvm::Value* inst = nullptr;

    //TODO:: 数组变量的声明
    //if( this->type->isArray ){
    inst = rt->builder.CreateAlloca(type);

    // a => "double"
    ctx.back()->types[varname] = stype;
    // a => llvm::value
    ctx.back()->locals[varname] = inst;

    Compiler::PrintSymTable(ctx);

    return inst;
}
/**
 *
 * @param rt
 * @param ctx
 * @param varname
 * @param value
 * @return
 */
llvm::Value* Compiler::declarationVar(Runtime* rt,std::deque<Context*> ctx,string varname,llvm::Value* value) {
    Debug("Create var declaration of varname:%s", varname.c_str());
    llvm::Type*  type = value->getType();
    if(value->getType()->isPointerTy()){
        //解引用
        auto ptr = rt->builder.CreateLoad(value, "ptr");
        type = ptr->getType();
    }
    llvm::Value* initial = nullptr;
    llvm::Value* inst = nullptr;

    /**
     * 因为变量的定义采用动态，所以这里是借助返回值来定义，那么如果返回值是一个指针 需要先解引用，否则会创建指针的指针
     */
     if(type->isPointerTy()){

     }

    //TODO:: 数组变量的声明
    //if( this->type->isArray ){
    inst = rt->builder.CreateAlloca(type);

    //TODO: 该根据value类型来设置动态类型 动态类型
    // a => "double"
    ctx.back()->types[varname] = "int";
    // a => nullptr
    ctx.back()->locals[varname] = inst;

    Compiler::PrintSymTable(ctx);

    return inst;
}


/**
 * 查找变量
 */
llvm::Value* Compiler::getVar(std::deque<Context*>& ctx,string name)
{
    for(auto it=ctx.rbegin(); it!=ctx.rend(); it++){
//        Debug("(*it)->locals[%s] = %s",name.c_str(),(*it)->locals[name].c_str());
        if( (*it)->locals.find(name) != (*it)->locals.end() ){
            return (*it)->locals[name];
        }
    }
    return nullptr;
}

llvm::Type*  Compiler::getVarType(Runtime* rt,string typeStr) {

    if( typeStr.compare("int") == 0 ){
        return llvm::Type::getInt32Ty(rt->llvmContext);
    }
    if( typeStr.compare("float") == 0 ){
        return llvm::Type::getFloatTy(rt->llvmContext);
    }
    if( typeStr.compare("double") == 0 ){
        return llvm::Type::getDoubleTy(rt->llvmContext);
    }
    if( typeStr.compare("bool") == 0 ){
        return llvm::Type::getInt1Ty(rt->llvmContext);
    }
    if( typeStr.compare("char") == 0 ){
        return llvm::Type::getInt8Ty(rt->llvmContext);
    }
    if( typeStr.compare("void") == 0 ){
        return llvm::Type::getVoidTy(rt->llvmContext);
    }
    if( typeStr.compare("string") == 0 ){
        return llvm::Type::getInt8PtrTy(rt->llvmContext);
    }
    if(typeStr.compare("void*") == 0){
        llvm::Type* v = llvm::Type::getVoidTy(rt->llvmContext);
        // 创建一个 int8** 指针
        return llvm::PointerType::get(v, 0);
    }

    //TODO: 支持结构体
//    if( this->_structTypes.find(typeStr) != this->_structTypes.end() )
//        return this->_structTypes[typeStr];

    return nullptr;
}
//这里已经是最低级的表达了，直接进行操作符运算即可
llvm::Value* Compiler::binaryOper(Runtime* rt,std::deque<Context*>& ctx,Token opt, llvm::Value* lhs, llvm::Value* rhs) {
    Debug("Create binary operator lhs.type:%s",Compiler::getTypeStr(lhs).c_str());
    bool fp = false;
     llvm::Value* L = lhs;
     llvm::Value* R = rhs;
    //判断如果是指针则需要转换
//    if(lhs->getType()->isPointerTy())
//        L = llvm::CastInst::Create(llvm::CastInst::PtrToInt,lhs, getVarType(rt,"int"), "cast", ctx.back()->block);
//    if(rhs->getType()->isPointerTy())
//        R = llvm::CastInst::Create(llvm::CastInst::PtrToInt,rhs, getVarType(rt,"int"), "cast", ctx.back()->block);

    if( (L->getType()->getTypeID() == llvm::Type::DoubleTyID) || (R->getType()->getTypeID() == llvm::Type::DoubleTyID) ){  // type upgrade
        fp = true;
        if( (R->getType()->getTypeID() != llvm::Type::DoubleTyID) )
            R = rt->builder.CreateUIToFP(R, llvm::Type::getDoubleTy(rt->llvmContext), "ftmp");
        if( (L->getType()->getTypeID() != llvm::Type::DoubleTyID) )
            L = rt->builder.CreateUIToFP(L, llvm::Type::getDoubleTy(rt->llvmContext), "ftmp");
    }

    if( !L || !R ){
        return nullptr;
    }
    Debug("fp=%s",std::string(fp ? "true" : "false" ).c_str());
    Debug("L type:%s",Compiler::getTypeStr(L).c_str());
    Debug("R type:%s",Compiler::getTypeStr(R).c_str());
    //TODO:支持更多的运算符
    switch (opt){
        case TK_ASSIGN:
            //赋值原先是有调用方来操作，现在和操作符放到同一个层级来操作
            rt->builder.CreateStore(R,L);
            return R;
        case TK_PLUS:
            return fp ? rt->builder.CreateFAdd(L, R, "addftmp") : rt->builder.CreateAdd(L, R, "addtmp");
        case TK_MINUS:
            return fp ? rt->builder.CreateFSub(L, R, "subftmp") : rt->builder.CreateSub(L, R, "subtmp");
        case TK_MUL:
            return fp ? rt->builder.CreateFMul(L, R, "mulftmp") : rt->builder.CreateMul(L, R, "multmp");
        case TK_DIV:
            return fp ? rt->builder.CreateFDiv(L, R, "divftmp") : rt->builder.CreateSDiv(L, R, "divtmp");
        case TK_BITAND:
//            return fp ? panic("Double type has no AND operation") : rt->builder.CreateAnd(L, R, "andtmp");
            return fp ? nullptr : rt->builder.CreateAnd(L, R, "andtmp");
        case TK_BITOR:
            return fp ? nullptr : rt->builder.CreateOr(L, R, "ortmp");
        case TK_BITXOR:
            return fp ? nullptr : rt->builder.CreateXor(L, R, "xortmp");
        case TK_SHIFTL:
            return fp ? nullptr : rt->builder.CreateShl(L, R, "shltmp");
        case TK_SHIFTR:
            return fp ? nullptr : rt->builder.CreateAShr(L, R, "ashrtmp");

        case TK_LT:
            return fp ? rt->builder.CreateFCmpULT(L, R, "cmpftmp") : rt->builder.CreateICmpULT(L, R, "cmptmp");
        case TK_LE:
            return fp ? rt->builder.CreateFCmpOLE(L, R, "cmpftmp") : rt->builder.CreateICmpSLE(L, R, "cmptmp");
        case TK_GE:
            return fp ? rt->builder.CreateFCmpOGE(L, R, "cmpftmp") : rt->builder.CreateICmpSGE(L, R, "cmptmp");
        case TK_GT:
            return fp ? rt->builder.CreateFCmpOGT(L, R, "cmpftmp") : rt->builder.CreateICmpSGT(L, R, "cmptmp");
        case TK_EQ:
            return fp ? rt->builder.CreateFCmpOEQ(L, R, "cmpftmp") : rt->builder.CreateICmpEQ(L, R, "cmptmp");
        case TK_NE:
            return fp ? rt->builder.CreateFCmpONE(L, R, "cmpftmp") : rt->builder.CreateICmpNE(L, R, "cmptmp");
        default:
            Error("Unknown binary operator");
            return nullptr;
    }
}
string Compiler::getSymbolType(std::deque<Context *> &ctx,string name) {
    for (int i = 0; i < ctx.size(); i++) {
//    for(it = ctx.rbegin(); it! = ctx.rend(); it++){
//            cout << "(*it)->locals[" << name << "] = " << (*it)->locals[name] << endl;
        if( (ctx.at(i))->types.find(name) != (ctx.at(i))->types.end() ){
            return (ctx.at(i))->types[name];
        }
    }
    return nullptr;
}

//打印变量表
void Compiler::PrintSymTable(std::deque<Context *> &ctx){
    cout << "======= Print Symbol Table ========" << endl;
    string prefix = "";
    for(auto it=ctx.begin(); it!=ctx.end(); it++){
        for(auto it2=(*it)->locals.begin(); it2!=(*it)->locals.end(); it2++){
            cout << prefix << it2->first << " = " << it2->second << ": " << getSymbolType(ctx,it2->first) << endl;
        }
        prefix += "\t";
    }
    cout << "===================================" << endl;
}

/**
 * 通过llvm::value 获取对应的类型 string，并和自己的类型系统关联起来
 * @param value
 * @return
 */
std::string Compiler::getTypeStr(llvm::Value *value){
    return typestr(value->getType());
}
std::string Compiler::getTypeStr(llvm::Type  *value){
    return typestr(value);
}
/**
 *
 * @param value
 * @return
 */
std::string typestr(llvm::Type* value){
    assert(value != nullptr);
    llvm::Type::TypeID typeID = value->getTypeID();

    switch (typeID){
        //0 bit
        case llvm::Type::VoidTyID:
            return "void";
        //16-bit floating point type
        case llvm::Type::HalfTyID:
            return "float16";
        //32-bit floating point type
        case llvm::Type::FloatTyID:
            return "float";
        //64-bit floating point type
        case llvm::Type::DoubleTyID:
            return "double";
        //80-bit floating point type (X87)
        case llvm::Type::X86_FP80TyID:
            return "float80";
        //128-bit floating point type (112-bit mantissa)
        case llvm::Type::FP128TyID:
            return "float128";
        //128-bit floating point type (two 64-bits, PowerPC)
        case llvm::Type::PPC_FP128TyID:
            return "double128";

        case llvm::Type::IntegerTyID:
            return "int";
        case llvm::Type::FunctionTyID:
            return "function";
        case llvm::Type::StructTyID:
            return "struct";
        case llvm::Type::ArrayTyID:
            return "array";
        case llvm::Type::PointerTyID:
            return "pointer";
        case llvm::Type::VectorTyID:
            return "vector";
        default:
            return "Unknown";
    }
}