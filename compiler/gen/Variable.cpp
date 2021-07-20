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

VarExpr* VarExpr::getVar(deque<Context*> ctx){
    getVarType(ctx);
    return ret;
}
/**
 * 获取真正的var，from local or params
 */
VarType VarExpr::getVarType(deque<Context*> ctx)
{
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    //检查全局变量,1s_local有两层含义
    //1. 在asm阶段表示是否为全局变量
    //2. 在语法阶段表示当前变量是否是一个包变量访问如: pkg1.global_name
    string package = this->package;
    if(!is_local){
        //说明这是一个成员变量访问
        if (ret = Context::getVar(ctx,package);ret != nullptr)
            return Var_Obj_Member;

        if (Package::packages.count(package)){
            ret  = Package::packages[package]->getGlobalVar(varname);
            //显式进行全局变量调用则需要强制检查
            if(ret) return Var_Extern_Global;
        }
    }
    //普通变量如果是一个全局变量则默认进行全局变量操作
    package = AsmGen::currentFunc->parser->getpkgname();
    ret  = Package::packages[package]->getGlobalVar(varname);
    if(ret) return Var_Local_Global;

    //通用本地变量|参数变量 变量遍历表 看是否存在
    ret = Context::getVar(ctx,this->varname);
    if(ret != nullptr){
        Function* f = AsmGen::currentFunc;
        //查看变量是属于参数变量还是函数块变量
        if(f->locals.count(varname))
            ret = f->locals[varname];
        else
            ret = f->params_var[varname];
        return Var_Local;
    }
    //3. 到这里还有一种情况,成员变量可以隐式访问（如果本地变量没有定义覆盖的情况下）
    if (ret = Context::getVar(ctx,"this");ret != nullptr) {
        return Var_Obj_Member;
    }
    //排除了以下的情况
    //1. 全局变量   （同包）
    //2. 全局包变量访问（不同包）
    //3. 本地变量
    //4. 隐式变量（当前在某个类的成员函数作用域内，默认会去寻找this.var）
    //触发第5种条件，需要处理函数名作为变量的情况，也就是函数指针
    Function* func = nullptr;
    funcpkg = this->package;
    if (Package::packages.count(funcpkg)){
        func = Package::packages[funcpkg]->getFunc(varname,false);
    }
    if(!func){
        funcpkg = AsmGen::currentFunc->parser->getpkgname();
        if (Package::packages.count(funcpkg)){
            func = Package::packages[funcpkg]->getFunc(varname,false);
        }
    }
    //函数名当做变量使用
    if(func){
        funcname = func->name;
        return Var_Func;
    }    

    parse_err("AsmError:use of undefined variable %s at line %d co %d\n",
          varname.c_str(),this->line,this->column);
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
    switch(getVarType(ctx))
    {
        case Var_Obj_Member: // 成员变量访问
            AsmGen::GenAddr(ret);
            AsmGen::Load();
            AsmGen::Push();
            //运算需要调用统一的方法
            Internal::object_member_get(varname);
            break;
        case Var_Extern_Global: //全局变量操作
        case Var_Local_Global:
            AsmGen::GenAddr(ret);
            AsmGen::Load();
            break;
        case Var_Local: //本地变量
            AsmGen::GenAddr(ret);
            //如果是var<i8-u64>基础类型则需要转换
            if(ret->structtype && !ret->pointer && ret->type <= KW_U64 && ret->type >= KW_I8)    
                AsmGen::Load(ret->size,ret->isunsigned);
            else                                    
                AsmGen::Load();
            break;
        case Var_Func:  //函数指针,函数名当做函数变量
            string fn = funcpkg + "_" + funcname;
            Debug("found function pointer:%s",fn.c_str());
            AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", fn.c_str());
            break;
    }
    return ret;
}
