/**
 *@ClassName Compiler
 *@Author brewlin
 *@Date 2020/9/10 0010 下午 3:33
 *@Version 1.0
 **/
#ifndef LANG_COMPILER_H
#define LANG_COMPILER_H

#include "Llvm.h"
#include "Runtime.h"
#include "Parser.h"

#include <string>
#include <memory>
#include <vector>
#include "Value.h"
#include <cstdlib>
#include "Log.h"

#define ISTYPE(value, id) (value->getType()->getTypeID() == id)

using namespace std;
using PointerT = llvm::PointerType*;

class Compiler{
    std::deque<Context*> ctx;
    Runtime* rt;
    Parser* p;
public:
    explicit Compiler(const std::string& filename);
    ~Compiler();
    void execute();
    void bin(const string& filename);
    void printIR();

public:

    //变量相关
    static llvm::Value* getVar(std::deque<Context*>& ctx,string name);
    static llvm::Value* setVar(Runtime* rt,std::deque<Context*>& ctx,string name,string stype);
    static llvm::Type*  getVarType(Runtime* rt,std::string typeStr);
    static llvm::Value* binaryOper(Runtime* rt,std::deque<Context*>& ctx,Token opt, llvm::Value* lhs, llvm::Value* rhs);
    static llvm::Value* declarationVar(Runtime* rt,std::deque<Context*> ctx,string varname,llvm::Value* value);
    static string       getSymbolType(std::deque<Context*>& ctx,string name);
    static void         PrintSymTable(std::deque<Context *> &ctx);
    static std::string  getTypeStr(llvm::Value* value);
    static std::string  getTypeStr(llvm::Type*  value);

    //函数相关
    static PointerT     getFuncPtr(Runtime* rt,Function* f);
    void                registerFunc();
    void                registerDefaultMain();
    static void         declarationFunc(Runtime* rt,std::deque<Context*> ctx,Function* f);
    static void         enterContext(std::deque<Context*>& ctx,llvm::BasicBlock* block);
    static void         leaveContext(std::deque<Context*>& ctx);

    //类型转换相关
    static llvm::Value* castToBoolean(Runtime* rt,llvm::Value* condValue);
    static void         addCast(llvm::Type *from, llvm::Type *to, llvm::CastInst::CastOps op);
    static llvm::Value* cast(llvm::Value *value, llvm::Type *type, llvm::BasicBlock *block);

    //结构体相关
    void                registerStruct();
    static void         declarationStruct(Runtime* rt,std::deque<Context*> ctx,Struct* s);
    static llvm::Value* getStructMember(Runtime* rt,std::deque<Context*> ctx,std::string varname,std::string membername);
    static void         initStruct(Runtime* rt,llvm::Value* obj,Struct* s);

};

//这个用于存放block栈信息，模拟函数调用的每个函数栈过程
extern std::map<llvm::Type*, std::map<llvm::Type*, llvm::CastInst::CastOps>> _castTable;


#endif //LANG_COMPILER_H
