/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"

//===---------------------------------------------------------------------===//
// 计算所有的表达式 并返回一个 void  结构，

void  NullExpr::asmgen(std::deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Null,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Null);

}
void  BoolExpr::asmgen(std::deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Bool,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Bool);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,25);
}
void  CharExpr::asmgen(
                         std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    Internal::newobject(Char,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Char);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,16);

}

void  IntExpr::asmgen( std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    Internal::newobject(Int,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld,%%rdi",Int);
//    AsmGen::writeln("    mov %%rdi, (%%rax)");
//    AsmGen::writeln("    mov $%ld,%%rdi",this->literal);
//    AsmGen::writeln("    mov %%rdi, %d(%%rax)", this->literal,4);

}

void  DoubleExpr::asmgen(std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Internal::newobject(Double,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld, (%%rax)", Double);
//    AsmGen::writeln("    mov $%ld, %d(%%rax)", this->literal,8);
}

void  StringExpr::asmgen(std::deque<Context*> ctx) {

//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    //string类型 传的是地址 需要调用方构造
    AsmGen::writeln("    lea %s(%%rip), %%rsi", name.c_str());
    Internal::newobject(String,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("    mov $%ld,%%rdi",String);
//    AsmGen::writeln("    mov %%rdi, (%%rax)", String);
//
//    AsmGen::writeln("    lea %s(%%rip), %%rdi", name.c_str());
//    AsmGen::writeln("    mov %%rdi, %d(%%rax)", 17);
}
void ClosureExpr::asmgen(std::deque<Context*> ctx){
    AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", varname.c_str());
}
/**
 * 赋值运算符 求值
 * @param ctx
 * @return
 */
void  AssignExpr::asmgen(std::deque<Context*> ctx){

//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Debug("AssignExpr: parsing... lhs:%s opt:%s rhs:%s",
          lhs->toString().c_str(),
          getTokenString(opt).c_str(),
          rhs->toString().c_str());
    if(!this->rhs)
        parse_err(
            "AsmError: right expression is wrong "
            "line:%d column:%d \n\n"
            "expression:\n%s\n",
            this->line,this->column,this->toString().c_str());

    //进行赋值 和 变量定义
    Function* f = AsmGen::currentFunc;

    //如果左值是一个标识符 表达式: a = 13;
    if(typeid(*lhs) == typeid(VarExpr)){
        VarExpr* varExpr = dynamic_cast<VarExpr*>(lhs);
        std::string package = AsmGen::currentFunc->parser->getpkgname() ;
        std::string varname = varExpr->varname;
        /*
         *1. 是否是包变量访问
         *2. 是否是类成员变量访问
         */
        if(!varExpr->is_local){

            package = varExpr->package;
            //说明这是一个成员变量访问
            if (auto *var = Context::getVar(ctx,package);var != nullptr) {
                //get var
                //获取object对象
                AsmGen::GenAddr(var);
                AsmGen::Load();
                AsmGen::Push();

                //获取右边值
                this->rhs->asmgen(ctx);
                AsmGen::Push();
                //运算需要调用统一的方法
                Internal::call_object_operator(this->opt,varname,"object_unary_operator");
                return;
            }
            //说明这是一个跨包访问
            varExpr = Package::packages[package]->getGlobalVar(varname);
            //显式进行全局变量调用则需要强制检查
            if(!varExpr) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
                varname.c_str(),this->line,this->column);
        //是否是全句变量
        }else if(Package::packages[package]->getGlobalVar(varname)){
            varExpr = Package::packages[package]->getGlobalVar(varname);
        }else if(f->params_var.count(varExpr->varname)){
            //1. 这个变量可能是函数参数变量，非本地变量
            varExpr = f->params_var[varExpr->varname];
            //这个变量一开始可能没有被注册过 需要手动注册到context中
            (ctx.back())->createVar(varExpr->varname,varExpr);
        }else{
            varExpr = f->locals[varExpr->varname];
            //这个变量一开始可能没有被注册过 需要手动注册到context中
            (ctx.back())->createVar(varExpr->varname,varExpr);
        }

        //f->locals 保存了本地变量的 唯一偏移量，所以需要通过name 来找到对应的 变量
        AsmGen::GenAddr(varExpr);
        //注意这里传入的是变量栈地址非 lhs的值
        AsmGen::Push();

        //对运算符右值求值
        this->rhs->asmgen(ctx);
        AsmGen::Push();
        //运算需要调用统一的方法
        Internal::call_operator(this->opt,"unary_operator");

        return;
    //索引赋值  a[0] = 1
    // arr_updateone(arr,index,var)
    }else if(typeid(*lhs) == typeid(IndexExpr))
    {
        IndexExpr* index    = dynamic_cast<IndexExpr*>(lhs);
        std::string varname = index->varname;
        VarExpr* varExpr;
        std::string package    = AsmGen::currentFunc->parser->getpkgname();
        //是否是包变量访问
        if(index->is_pkgcall){
            package = index->package;
            varExpr = Package::packages[package]->getGlobalVar(varname);
            //显式进行全局变量调用则需要强制检查
            if(!varExpr) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
                varname.c_str(),this->line,this->column);
        //是否是全句变量
        }else if(Package::packages[package]->getGlobalVar(varname)){
            varExpr = Package::packages[package]->getGlobalVar(varname);
        }else if(f->params_var.count(varname)){
            //1. 这个变量可能是函数参数变量，非本地变量
            varExpr = f->params_var[varname];
        }else{
            varExpr = f->locals[varname];
        }
        if(!varExpr)
            parse_err("SyntaxError: not find variable %s at line %d, %col\n", varname.c_str(),line,column);
        //这个变量一开始可能没有被注册过 需要手动注册到context中
        (ctx.back())->createVar(varExpr->varname,varExpr);

        //push arr 获取数组偏移量
        AsmGen::GenAddr(varExpr);
        AsmGen::Load();
        AsmGen::Push();

        //push index 计算索引
        if(!index->index) {
            rhs->asmgen(ctx);
            AsmGen::Push();

            Internal::arr_pushone();
            AsmGen::Pop("%rdi");
           return;
        }

        index->index->asmgen(ctx);
        AsmGen::Push();

        rhs->asmgen(ctx);
        AsmGen::Push();

        //call arr_updateone(arr,index,var)
        Internal::kv_update();
        //rm unuse 
        AsmGen::Pop("%rdi");
        return;
    }
    parse_err("SyntaxError: can not assign to %s at line %d, %col\n", typeid(lhs).name(),line,column);
}

/**
 * 二元运算符求值
 * @param ctx
 * @return
 */
void  BinaryExpr::asmgen(std::deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Debug("BinaryExpr: parsing... lhs:%s opt:%s rhs:%s",
          lhs->toString().c_str(),
          getTokenString(opt).c_str(),
          rhs->toString().c_str());
    if(!this->rhs)
        parse_err(
            "AsmError: right expression is wrong "
            "line:%d column:%d \n\n"
            "expression:\n%s\n",
            this->line,this->column,this->toString().c_str());

    //保存rax寄存器的值 因为下面右值计算的时候会用到rax寄存器
    this->lhs->asmgen(ctx);
    AsmGen::Push();

    //对运算符右值求值
    this->rhs->asmgen(ctx);
    AsmGen::Push();

    //运算需要调用统一的方法
    Internal::call_operator(this->opt,"binary_operator");
}


/**
 * 链式表达式
 * @param ctx
 * @return
 */
void  ChainExpr::asmgen(std::deque<Context*> ctx)
{
    std::cout << this->toString() << std::endl;
}