/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Expression.h"
#include "AsmGen.h"
#include "Log.h"
#include "Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"

//===---------------------------------------------------------------------===//
// 计算所有的表达式 并返回一个 void  结构，

void  NullExpr::asmgen(std::deque<Context*> ctx)
{
    Internal::newobject(Null,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Null);

}
void  BoolExpr::asmgen(std::deque<Context*> ctx)
{
    Internal::newobject(Bool,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Bool);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,25);
}
void  CharExpr::asmgen(
                         std::deque<Context*> ctx) {

    Internal::newobject(Char,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Char);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,16);

}

void  IntExpr::asmgen( std::deque<Context*> ctx) {

    Internal::newobject(Int,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld,%%rdi",Int);
//    AsmGen::writeln("  mov %%rdi, (%%rax)");
//    AsmGen::writeln("  mov $%ld,%%rdi",this->literal);
//    AsmGen::writeln("  mov %%rdi, %d(%%rax)", this->literal,4);

}

void  DoubleExpr::asmgen(
                           std::deque<Context*> ctx) {
    Internal::newobject(Double,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Double);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,8);


}

void  StringExpr::asmgen(
                         std::deque<Context*> ctx) {

    //string类型 传的是地址 需要调用方构造
    AsmGen::writeln("  lea %s(%%rip), %%rsi", name.c_str());
    Internal::newobject(String,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld,%%rdi",String);
//    AsmGen::writeln("  mov %%rdi, (%%rax)", String);
//
//    AsmGen::writeln("  lea %s(%%rip), %%rdi", name.c_str());
//    AsmGen::writeln("  mov %%rdi, %d(%%rax)", 17);

}
/**
 * 数组变量生成
 * @param ctx
 * @return
 */
void  ArrayExpr::asmgen(std::deque<Context*> ctx){
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
 * asm gen map
 * @param ctx
 */
void  MapExpr::asmgen(std::deque<Context*> ctx){
    Debug("MapExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());

    //new array & push array
    Internal::newobject(Map, 0);
    AsmGen::Push();

    for(auto& element: this->literal){
        //new element & push element
        element->asmgen(ctx);
        Internal::kv_update();
    }

    //pop array
    AsmGen::Pop("%rax");
}
/**
 * asm gen key value
 * @param ctx
 */
void  KVExpr::asmgen(std::deque<Context*> ctx){
    Debug("KVExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());

    //push key
    this->key->asmgen(ctx);
    AsmGen::Push();
    //push value
    this->value->asmgen(ctx);
    AsmGen::Push();
}

/**
 * load 变量,这里说明一下: 所有变量的读取如果没有显示指明跨包访问全局变量则默认进行当前全局变量访问
 * 1 计算偏移量
 * 2 加载变量
 * @param ctx
 * @return
 */
void  VarExpr::asmgen(std::deque<Context*> ctx){
    VarExpr* var;
    //检查全局变量,1s_local有两层含义
    //1. 在asm阶段表示是否为全局变量
    //2. 在语法阶段表示当前变量是否是一个包变量访问如: pkg1.global_name
    if(!is_local){
        std::string gname = package + "." + varname;
        var  = Package::packages[package]->getGlobalVar(gname);
        //显式进行全局变量调用则需要强制检查
        if(!var) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
            gname.c_str(),this->line,this->column);
        AsmGen::GenAddr(var,is_delref);
        if(!is_delref) AsmGen::Load();
        return;
    }
    //普通变量如果是一个管局变量则默认进行全局变量操作
    std::string gname = AsmGen::currentFunc->parser->getpkgname() + "." + varname;
    var  = Package::packages[AsmGen::currentFunc->parser->getpkgname()]->getGlobalVar(gname);
    if(var){
        AsmGen::GenAddr(var,is_delref);
        if(!is_delref) AsmGen::Load();
        return;
    }

    //变量遍历表 看是否存在
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
        auto* ctx = *p;

        if(auto* var = ctx->getVar(this->varname);var != nullptr)
        {

            Function* f = AsmGen::currentFunc;
            //查看变量是属于哪种变量
            if(f->locals.count(varname))
                var = f->locals[varname];
            else
                var = f->params_var[varname];

            AsmGen::GenAddr(var,is_delref);
            //如果是解引用就需要在 读取变量了，否则这个变量是直接传递给下游
            if(!is_delref)
                AsmGen::Load();
            return;
        }
    }
    parse_err("AsmError:use of undefined variable %s at line %d co %d\n",
          varname.c_str(),this->line,this->column);
}
/**
 * 索引 数组
 * @param ctx
 * @return
 */
void  IndexExpr::asmgen(std::deque<Context*> ctx) {
    VarExpr* var;
    //看看是否是包变量调用
    if(is_pkgcall){
        std::string gname = package + "." + varname;
        var  = Package::packages[package]->getGlobalVar(gname);
        //显式进行全局变量调用则需要强制检查
        if(!var) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
            gname.c_str(),this->line,this->column);
    }else{
        //普通变量如果是一个管局变量则默认进行全局变量操作
        std::string gname = AsmGen::currentFunc->parser->getpkgname() + "." + varname;
        var  = Package::packages[AsmGen::currentFunc->parser->getpkgname()]->getGlobalVar(gname);
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

/**
 * 函数调用求值
 * @param ctx
 * @return
 */
void  FunCallExpr::asmgen(std::deque<Context*> ctx)
{
    Debug("FunCallExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());
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
    std::string realfuncname = this->package + "." + funcname;
    std::string callpkg      = this->package;
    if(!is_pkgcall){
        realfuncname = cfunc->parser->getpkgname() + "." + this->funcname;
        callpkg      = cfunc->parser->getpkgname();
    }

    //判断是否是进行外部函数调用
    bool is_extern = false;
    if(this->package == "_"){
        realfuncname = cfunc->parser->getpkgname() + "." + this->funcname;
        callpkg      = cfunc->parser->getpkgname();
        is_extern = true;
    }
    Package *pkg  = Package::packages[callpkg];
    //函数查找
    if(auto* func = pkg->getFunc(realfuncname,is_extern); func != nullptr)
    {

        //只会进行提示，现在默认已实现不足6个参数会默认置0
        if(func->params.size() != this->args.size())
            Debug("ArgumentError: expects %d arguments but got %d\n",(int)func->params.size(),(int)this->args.size());

        int stack_args = AsmGen::Push_arg(ctx,args,func->is_variadic,funcname);

        //如果没有可变参数传参  默认执行 通用寄存器赋值即可
        if(!cfunc || !cfunc->is_variadic || !have_variadic)
            //这里是对 rdi  rsi rdx rcx r8 r9 寄存器传参赋值
            for (int i = 0; i < GP_MAX; ++i)
                AsmGen::Pop(AsmGen::argreg64[gp++]);

        //需要判断是不是外部链接函数，否则需要加上包名
        if(func->isExtern)
            AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        else
            AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", realfuncname.c_str());

        AsmGen::writeln("  mov %%rax, %%r10");
        AsmGen::writeln("  mov $%d, %%rax", fp);
        AsmGen::writeln("  call *%%r10");


        //如果当前函数调用存在解引用可变参数则需要动态计算函数栈上移的大小
        if(AsmGen::currentFunc && AsmGen::currentFunc->is_variadic && have_variadic)
        {
            int c = AsmGen::count++;
            AsmGen::writeln("  mov -8(%%rbp),%%rdi");
            AsmGen::writeln("  mov %%rdi,%d(%%rbp)",AsmGen::currentFunc->stack);
            AsmGen::writeln("  sub $-7,%d(%%rbp)",AsmGen::currentFunc->stack);
            //判断如果此时有栈参数则需要去除
            AsmGen::writeln("  cmp $0,%d(%%rbp)",AsmGen::currentFunc->stack);
            AsmGen::writeln("  jle .L.if.end.%d",c);
            AsmGen::writeln("  cmp %d(%%rbp),%%rdi",AsmGen::currentFunc->stack);
            AsmGen::writeln("  add %%rdi, %%rsp", stack_args * 8);
            AsmGen::writeln(".L.if.end.%d:",c);
        }else{
            AsmGen::writeln("  add $%d, %%rsp", stack_args * 8);

        }
        return;

    }
    parse_err(
            "AsmError: can not find function definition of %s "
            "line:%d column:%d \n\n"
            "expression:\n%s\n",
            funcname.c_str(),this->line,this->column,this->toString().c_str());
}
/**
 * 赋值运算符 求值
 * @param ctx
 * @return
 */
void  AssignExpr::asmgen(std::deque<Context*> ctx){

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
        std::string cpkgname = AsmGen::currentFunc->parser->getpkgname() ;
        std::string gname    = cpkgname + "." + varExpr->varname;
        //是否是包变量访问
        if(!varExpr->is_local){
            gname = varExpr->package + "." + varExpr->varname;
            varExpr = Package::packages[varExpr->package]->getGlobalVar(gname);
            //显式进行全局变量调用则需要强制检查
            if(!varExpr) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
                gname.c_str(),this->line,this->column);
        //是否是全句变量
        }else if(Package::packages[cpkgname]->getGlobalVar(gname)){
            varExpr = Package::packages[cpkgname]->getGlobalVar(gname);
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
        std::string cpkgname = AsmGen::currentFunc->parser->getpkgname();
        std::string gname    = cpkgname + "." + varname;
        //是否是包变量访问
        if(index->is_pkgcall){
            gname = index->package + "." + varname;
            varExpr = Package::packages[index->package]->getGlobalVar(gname);
            //显式进行全局变量调用则需要强制检查
            if(!varExpr) parse_err("AsmError:use of undefined global variable %s at line %d co %d\n",
                gname.c_str(),this->line,this->column);
        //是否是全句变量
        }else if(Package::packages[cpkgname]->getGlobalVar(gname)){
            varExpr = Package::packages[cpkgname]->getGlobalVar(gname);
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
 * TODO: new expr
 * 针对结构体的变量定义
 * b = new Http
 * @param ctx
 * @return
 */
void  NewExpr::asmgen(std::deque<Context*> ctx)
{

}
/**
 *
 * TODO: asm struct
 * @param ctx
 * @return
 */
void  MemberExpr::asmgen(std::deque<Context*> ctx)
{
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

