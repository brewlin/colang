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
 * 数组变量生成
 * @param ctx
 * @return
 */
void  ArrayExpr::asmgen(std::deque<Context*> ctx){
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    //new array & push array
    Internal::newobject(Array, 0);
    AsmGen::Push();

    for(auto& element: this->literal){
        //new element & push element
        element->asmgen(ctx);
        AsmGen::Push();
        Internal::arr_pushone();
    }

    //pop array
    AsmGen::Pop("%rax");

}

/**
 * asm gen key value
 * @param ctx
 */
void  KVExpr::asmgen(std::deque<Context*> ctx){
    Debug("KVExpr: gen... k:%s v:%s",key->toString().c_str(),value->toString());
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    //push key
    this->key->asmgen(ctx);
    AsmGen::Push();
    //push value
    this->value->asmgen(ctx);
    AsmGen::Push();
}

/**
 * 索引 数组
 * @param ctx
 * @return
 */
void  IndexExpr::asmgen(std::deque<Context*> ctx) {
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);
    VarExpr* var;
    std::string   package = this->package;
    std::cout << "varname:" << varname << std::endl;
    //看看是否是包变量调用
    if(is_pkgcall){
        var  = Package::packages[package]->getGlobalVar(varname);
        //显式进行全局变量调用则需要强制检查
        if(!var) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
            varname.c_str(),this->line,this->column);
    }else{
        //普通变量如果是一个管局变量则默认进行全局变量操作
        package = AsmGen::currentFunc->parser->getpkgname();
        var  = Package::packages[package]->getGlobalVar(varname);
    }
    if(var){
        //push arr 获取数组偏移量
        AsmGen::GenAddr(var);
        AsmGen::Load();
        AsmGen::Push();

        //push index 计算索引
        this->index->asmgen(ctx);
        AsmGen::Push();

        //call arr_get(arr,index)
        Internal::kv_get();
        return;
    }
    //接下来就是本地变量和 本地函数参数
    for (auto p = ctx.crbegin(); p != ctx.crend(); ++p) {
        auto *context = *p;

        if (auto *var = context->getVar(this->varname);var != nullptr) {
            Function* f = AsmGen::currentFunc;
            //查看变量是属于哪种变量
            if(f->locals.count(varname))
                var = f->locals[varname];
            else
                var = f->params_var[varname];

            //push arr 获取数组偏移量
            AsmGen::GenAddr(var);
            AsmGen::Load();
            AsmGen::Push();

            //push index 计算索引
            this->index->asmgen(ctx);
            AsmGen::Push();

            //call arr_get(arr,index)
            Internal::kv_get();
            return;
        }
    }
    //没找到 数组变量 抛出异常 exit退出
    parse_err("AsmError: index-expr use of undefined variable %s at line %d col %d\n",varname.c_str(),line,column);
}

