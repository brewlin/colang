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
 * TODO: new expr
 * 针对结构体的变量定义
 * b = new Http
 * @param ctx
 * @return
 */
void  NewExpr::asmgen(std::deque<Context*> ctx)
{

//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    Debug("new expr got: type:%s",this->type.c_str());
    //获取struct 类型
    Class* s = AsmGen::parser->getClass(this->type);
    if(!s){
        parse_err(
                "AsmError: class is not define of %s "
                "line:%d column:%d \n\n",
                type.c_str(),this->line,this->column);
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
void  MemberExpr::asmgen(std::deque<Context*> ctx)
{
    //func().var 链式表达
    if(varname == ""){
        //运算需要调用统一的方法
        Internal::object_member_get(membername);
        return;

    }
    auto *var = Context::getVar(ctx,varname);
    //get var
    //获取object对象
    AsmGen::GenAddr(var);
    AsmGen::Load();
    AsmGen::Push();
    //运算需要调用统一的方法
    Internal::object_member_get(membername);
    return;
}
/**
 * TODO: asm struct call
 * @param ctx
 * @return
 */
void  MemberCallExpr::asmgen(std::deque<Context*> ctx)
{
    Debug("membercall : ")
}

