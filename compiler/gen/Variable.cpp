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

using namespace std;

VarExpr* realVar(deque<Context*> ctx,VarExpr* origin)
{
    VarExpr* var;
    string varname = origin->varname;
    //检查全局变量,1s_local有两层含义
    //1. 在asm阶段表示是否为全局变量
    //2. 在语法阶段表示当前变量是否是一个包变量访问如: pkg1.global_name
    string package = origin->package;
    if(!origin->is_local){
        //说明这是一个成员变量访问
        if (auto *var = Context::getVar(ctx,package);var != nullptr) {
            return var;
        }
        if (Package::packages.count(package)){
            var  = Package::packages[package]->getGlobalVar(varname);
            //显式进行全局变量调用则需要强制检查
            if(var){
                return var;
            } 
        }
    }
    //普通变量如果是一个全局变量则默认进行全局变量操作
    package = AsmGen::currentFunc->parser->getpkgname();
    var  = Package::packages[package]->getGlobalVar(varname);
    if(var){
        return var;
    }

    //变量遍历表 看是否存在
    var = Context::getVar(ctx,varname);
    if(var != nullptr){
        Function* f = AsmGen::currentFunc;
        //查看变量是属于参数变量还是函数块变量
        if(f->locals.count(varname))
            var = f->locals[varname];
        else
            var = f->params_var[varname];
        return var;
    }
    //3. 到这里还有一种情况,成员变量可以隐式访问（如果本地变量没有定义覆盖的情况下）
    if (auto *var = Context::getVar(ctx,"this");var != nullptr) {
        return var;
    }
    return nullptr;
}
/**
 * load 变量,这里说明一下: 所有变量的读取如果没有显示指明跨包访问全局变量则默认进行当前全局变量访问
 * 1 计算偏移量
 * 2 加载变量
 * @param ctx
 * @return
 */
Expression*  VarExpr::asmgen(deque<Context*> ctx){
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    VarExpr* var;
    //检查全局变量,1s_local有两层含义
    //1. 在asm阶段表示是否为全局变量
    //2. 在语法阶段表示当前变量是否是一个包变量访问如: pkg1.global_name
    string package = this->package;
    if(!is_local){
        //说明这是一个成员变量访问
        if (auto *var = Context::getVar(ctx,package);var != nullptr) {
            //get var
            //获取object对象
            AsmGen::GenAddr(var);
            AsmGen::Load();
            AsmGen::Push();
            //运算需要调用统一的方法
            Internal::object_member_get(varname);
            return nullptr;
        }
        if (Package::packages.count(package)){
            var  = Package::packages[package]->getGlobalVar(varname);
            //显式进行全局变量调用则需要强制检查
            if(var){
                AsmGen::GenAddr(var);
                AsmGen::Load();
                return nullptr;
            } 
        }
    }
    //普通变量如果是一个全局变量则默认进行全局变量操作
    package = AsmGen::currentFunc->parser->getpkgname();
    var  = Package::packages[package]->getGlobalVar(varname);
    if(var){
        AsmGen::GenAddr(var);
        AsmGen::Load();
        return nullptr;
    }

    //变量遍历表 看是否存在
    var = Context::getVar(ctx,this->varname);
    if(var != nullptr){
        Function* f = AsmGen::currentFunc;
        //查看变量是属于参数变量还是函数块变量
        if(f->locals.count(varname))
            var = f->locals[varname];
        else
            var = f->params_var[varname];

        AsmGen::GenAddr(var);
        AsmGen::Load();
        return nullptr;
    }
    //3. 到这里还有一种情况,成员变量可以隐式访问（如果本地变量没有定义覆盖的情况下）
    if (auto *var = Context::getVar(ctx,"this");var != nullptr) {
        //get var
        //获取object对象
        AsmGen::GenAddr(var);
        AsmGen::Load();
        AsmGen::Push();
        //运算需要调用统一的方法
        Internal::object_member_get(varname);
        return nullptr;
    }
    //排除了以下的情况
    //1. 全局变量   （同包）
    //2. 全局包变量访问（不同包）
    //3. 本地变量
    //4. 隐式变量（当前在某个类的成员函数作用域内，默认会去寻找this.var）
    //触发第5种条件，需要处理函数名作为变量的情况，也就是函数指针
    Function* func = nullptr;
    package = this->package;
    if (Package::packages.count(package)){
        func = Package::packages[package]->getFunc(varname,false);
    }
    if(!func){
        package = AsmGen::currentFunc->parser->getpkgname();
        if (Package::packages.count(package)){
            func = Package::packages[package]->getFunc(varname,false);
        }
    }
    if(func){
        string funcname = package + "_" + func->name;
        Debug("found function pointer:%s",funcname.c_str());
        AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        return nullptr;
    }


    parse_err("AsmError:use of undefined variable %s at line %d co %d\n",
          varname.c_str(),this->line,this->column);
}
