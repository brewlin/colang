/*
 * @author brewlin
 * @date   2021/6/9
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"

/**
 * 函数调用求值
 * @param ctx
 * @return
 */
void  FunCallExpr::asmgen(std::deque<Context*> ctx)
{
    Debug("FunCallExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    //gp 通用寄存器个数统计
    //fp 浮点数寄存器个数统计
    int gp = 0, fp = 0;

    //判断是否有可变参数
    bool have_variadic = false;
    Function* cfunc = AsmGen::currentFunc;
    for(auto arg : args){
        if (typeid(*arg) == typeid(VarExpr) && cfunc){
            VarExpr* var = dynamic_cast<VarExpr*>(arg);
            if(auto res = cfunc->params_var.find(var->varname) ; res != cfunc->params_var.end()){
                VarExpr* var2  = res->second;
                if(var2->is_variadic)
                    have_variadic = true;
            }
        }
    }
    //如果没有加包名 就默认加上当前包名进行调用
    std::string package = this->package;
    if(!is_pkgcall){
        package      = cfunc->parser->getpkgname();
    }

    //判断是否是进行外部函数调用
    bool is_extern = false;
    if(this->package == "_"){
        package      = cfunc->parser->getpkgname();
        is_extern = true;
    }

    Function *func;
    //说明这是一个对象成员函数调用
    if (auto *var = Context::getVar(ctx,package);var != nullptr) {
        //get var
        //获取object对象
        AsmGen::GenAddr(var);
        AsmGen::Load();
        AsmGen::Push();
        Internal::object_func_addr(funcname);
        //获取到成员函数的函数地址
        AsmGen::Push();
        //构造一个假的function
        func = new Function;
        func->isExtern    = false;
        func->isObj       = true;
        func->is_variadic = false;
        //函数名也是当前局域内的一个变量，说明是一种函数指针调用
    }else if (auto *var = Context::getVar(ctx,funcname);var != nullptr) {
        //get var
        //获取var值
        AsmGen::GenAddr(var);
        AsmGen::Load();
        AsmGen::Push();
        //构造一个假的function
        func = new Function;
        func->isExtern    = false;
        func->isObj       = true;
        func->is_variadic = false;
    }else{
        Package *pkg  = Package::packages[package];
        if(!pkg){
            parse_err(
                    "AsmError: can not find package definition of %s "
                    "line:%d column:%d \n\n"
                    "expression:\n%s\n",
                    package.c_str(),this->line,this->column,this->toString().c_str());
        }
        //函数查找
        func = pkg->getFunc(funcname,is_extern);
        if(!func)
            parse_err(
                    "AsmError: can not find package definition of %s "
                    "line:%d column:%d \n\n"
                    "expression:\n%s\n",
                    package.c_str(),this->line,this->column,this->toString().c_str());
        func->isObj       = false;
        if(func == nullptr)
            parse_err(
                    "AsmError: can not find function definition of %s "
                    "line:%d column:%d \n\n"
                    "expression:\n%s\n",
                    funcname.c_str(),this->line,this->column,this->toString().c_str());
    }

    //只会进行提示，现在默认已实现不足6个参数会默认置0
    if(func->params.size() != this->args.size())
        Debug("ArgumentError: expects %d arguments but got %d\n",(int)func->params.size(),(int)this->args.size());

    int stack_args = AsmGen::Push_arg(ctx,args,func->is_variadic,funcname);

    //如果没有可变参数传参  默认执行 通用寄存器赋值即可
    if(!cfunc || !cfunc->is_variadic || !have_variadic)
        //这里是对 rdi  rsi rdx rcx r8 r9 寄存器传参赋值
        for (int i = 0; i < GP_MAX; ++i)
            AsmGen::Pop(AsmGen::argreg64[gp++]);
    if(!func->isObj){
        //需要判断是不是外部链接函数，否则需要加上包名
        if(func->isExtern){
            AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        }else{
            std::string realfuncname = package + "_" + funcname;
            AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", realfuncname.c_str());
        }

        AsmGen::writeln("    mov %%rax, %%r10");
        AsmGen::writeln("    mov $%d, %%rax", fp);
        AsmGen::writeln("    call *%%r10");
    }else{
        AsmGen::Pop("%r10");
        AsmGen::writeln("    mov $%d, %%rax", fp);
        AsmGen::writeln("    call *%%r10");
    }


    //如果当前函数调用存在解引用可变参数则需要动态计算函数栈上移的大小
    if(AsmGen::currentFunc && AsmGen::currentFunc->is_variadic && have_variadic)
    {
        int c = AsmGen::count++;
        AsmGen::writeln("    mov -8(%%rbp),%%rdi");
        AsmGen::writeln("    mov %%rdi,%d(%%rbp)",AsmGen::currentFunc->stack);
        AsmGen::writeln("    sub $-7,%d(%%rbp)",AsmGen::currentFunc->stack);
        //判断如果此时有栈参数则需要去除
        AsmGen::writeln("    cmp $0,%d(%%rbp)",AsmGen::currentFunc->stack);
        AsmGen::writeln("    jle L.if.end.%d",c);
        AsmGen::writeln("    cmp %d(%%rbp),%%rdi",AsmGen::currentFunc->stack);
        AsmGen::writeln("    add %%rdi, %%rsp", stack_args * 8);
        AsmGen::writeln("L.if.end.%d:",c);
    }else{
        AsmGen::writeln("    add $%d, %%rsp", stack_args * 8);

    }
    return;

}