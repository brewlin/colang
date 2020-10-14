/**
 *@ClassName CompilerCast
 *@Author brewlin
 *@Date 2020/9/27 0027 下午 3:28
 *@Version 1.0
 **/
#include "Compiler.h"
#include "Log.h"

std::map<llvm::Type*, std::map<llvm::Type*, llvm::CastInst::CastOps>> _castTable;

llvm::Value* Compiler::castToBoolean(Runtime* rt,llvm::Value* condValue)
{
    if( ISTYPE(condValue, llvm::Type::IntegerTyID) ){
        condValue = rt->builder.CreateIntCast(condValue, llvm::Type::getInt1Ty(rt->llvmContext), true);
        return rt->builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(rt->llvmContext), 0, true));
    }else if( ISTYPE(condValue, llvm::Type::DoubleTyID) ){
        return rt->builder.CreateFCmpONE(condValue, llvm::ConstantFP::get(rt->llvmContext, llvm::APFloat(0.0)));
    }else{
        return condValue;
    }
}
//用于类型转换
void Compiler::addCast(llvm::Type*  from, llvm::Type*  to, llvm::CastInst::CastOps op) {
    if( _castTable.find(from) == _castTable.end() ){
        _castTable[from] = std::map<llvm::Type*, llvm::CastInst::CastOps>();
    }
    _castTable[from][to] = op;
}
//这里表示进行类型转换
llvm::Value* Compiler::cast(llvm::Value *value, llvm::Type*  type, llvm::BasicBlock *block) {

    llvm::Type* from = value->getType();
    Debug("cast type from:%s to:%s",Compiler::getTypeStr(value).c_str(),Compiler::getTypeStr(type).c_str());
    for(auto it=_castTable.begin(); it!=_castTable.end(); it++) {
        Debug("name:%s",Compiler::getTypeStr(it->first).c_str());
    }
    if( from == type )
        return value;
    if( _castTable.find(from) == _castTable.end() ){
        Error("Type has no cast");
        return value;
    }
    if( _castTable[from].find(type) == _castTable[from].end() ){
        std::string e = Compiler::getTypeStr(from) + " to " + Compiler::getTypeStr(type);
        Error("Unable to cast from %s",e.c_str());
        return value;
    }

    return llvm::CastInst::Create(_castTable[from][type], value, type, "cast", block);
}