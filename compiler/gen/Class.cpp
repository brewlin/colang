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
 * new struct
 * 针对结构体的变量new
 * new 200
 */
Expression*  NewExpr::asmgen(std::deque<Context*> ctx)
{
    //查看是不是结构体变量
    string package = AsmGen::parser->import[this->package];
    if(Package::packages.count(package) > 0){
        Struct* s = nullptr;
        if((s = Package::packages[package]->getStruct(name)) && s != nullptr){
            // cout << s->size <<endl;
            // for(auto i : s->member){
                // cout << i->name <<":" << i->offset <<endl;
            // }
            Internal::gc_malloc(s->size);
            return this;
        }
    }
    AsmGen::writeln("   mov $0,%%rax");
    return this;
}

/**
 * b = new Http
 * @param ctx
 * @return
 */
Expression*  NewClassExpr::asmgen(std::deque<Context*> ctx)
{

//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Debug("new expr got: type:%s",this->name.c_str());
    //获取class 类型
    //处理映射
    Class* s = nullptr;
    if(package != ""){
        string realPkg = AsmGen::parser->import[package];
        Package* pkg = Package::packages[realPkg];
        if(pkg){
            s = pkg->getClass(this->name);
        }
    }else{
        s = AsmGen::parser->pkg->getClass(this->name);
    }
    if(!s){
        parse_err(
                "AsmError: class is not define of %s "
                "line:%d column:%d \n\n",
                name.c_str(),this->line,this->column);
    }
    Internal::newobject(Object,s->funcs.size());
    AsmGen::Push();

    for(auto func : s->funcs){
        std::string funcname = func->parser->getpkgname() +
                               "_" + s->name + "_" + func->name;
        AsmGen::writeln("    mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        AsmGen::Push();
        Internal::object_func_add(func->name);
    }
    AsmGen::Pop("%rax");

}
/**
 *
 * TODO: asm struct
 * @param ctx
 * @return
 */
Expression*  MemberExpr::asmgen(std::deque<Context*> ctx)
{
    //func().var 链式表达
    if(varname == ""){
        //运算需要调用统一的方法
        Internal::object_member_get(membername);
        return nullptr;

    }
    auto *var = Context::getVar(ctx,varname);
    //get var
    //获取object对象
    AsmGen::GenAddr(var);
    AsmGen::Load();
    AsmGen::Push();
    //运算需要调用统一的方法
    Internal::object_member_get(membername);
    return nullptr;
}
/**
 * TODO: asm struct call
 * @param ctx
 * @return
 */
Expression*  MemberCallExpr::asmgen(std::deque<Context*> ctx)
{
    Debug("membercall : ")
}

