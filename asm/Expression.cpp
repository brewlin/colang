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

void  NullExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    Internal::newobject(Null,0);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Null);

}
void  BoolExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    Internal::newobject(Bool,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Bool);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,25);
}
void  CharExpr::asmgen(Runtime* rt,
                         std::deque<Context*> ctx) {

    Internal::newobject(Char,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Char);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,16);

}

void  IntExpr::asmgen(Runtime* rt, std::deque<Context*> ctx) {

    Internal::newobject(Int,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld,%%rdi",Int);
//    AsmGen::writeln("  mov %%rdi, (%%rax)");
//    AsmGen::writeln("  mov $%ld,%%rdi",this->literal);
//    AsmGen::writeln("  mov %%rdi, %d(%%rax)", this->literal,4);

}

void  DoubleExpr::asmgen(Runtime* rt,
                           std::deque<Context*> ctx) {
    Internal::newobject(Double,this->literal);
//    Internal::gc_malloc();
//    AsmGen::writeln("  mov $%ld, (%%rax)", Double);
//    AsmGen::writeln("  mov $%ld, %d(%%rax)", this->literal,8);


}

void  StringExpr::asmgen(Runtime* rt,
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
 * @param rt
 * @param ctx
 * @return
 */
void  ArrayExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    //new array & push array
    Internal::newobject(Array, 0);
    AsmGen::Push();

    for(auto& element: this->literal){
        //new element & push element
        element->asmgen(rt,ctx);
        AsmGen::Push();
        Internal::arr_pushone();
    }

    //pop array
    AsmGen::Pop("%rax");

}
/**
 * asm gen map
 * @param rt
 * @param ctx
 */
void  MapExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    Debug("MapExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());
}
/**
 * asm gen key value
 * @param rt
 * @param ctx
 */
void  KVExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    Debug("KVExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());
}

/**
 * load 变量
 * 1 计算偏移量
 * 2 加载变量
 * @param rt
 * @param ctx
 * @return
 */
void  IdentExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){

    //变量遍历表 看是否存在
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
        auto* ctx = *p;

        if(auto* var = ctx->getVar(this->identname);var != nullptr)
        {

            Function* f = AsmGen::currentFunc;
            //查看变量是属于哪种变量
            if(f->locals.count(identname))
                var = f->locals[identname];
            else
                var = f->params_var[identname];

            AsmGen::GenAddr(var,is_delref);
            //如果是解引用就需要在 读取变量了，否则这个变量是直接传递给下游
            if(!is_delref)
                AsmGen::Load();
            return;
        }
    }
    parse_err("AsmError:use of undefined variable %s at line %d co %d\n",
          identname.c_str(),this->line,this->column);
}
/**
 * 索引 数组
 * @param rt a[1]
 * @param ctx
 * @return
 */
void  IndexExpr::asmgen(Runtime* rt,std::deque<Context*> ctx) {
    //变量遍历表 看是否存在
    for (auto p = ctx.crbegin(); p != ctx.crend(); ++p) {
        auto *context = *p;

        if (auto *var = context->getVar(this->identname);var != nullptr) {
            Function* f = AsmGen::currentFunc;
            //查看变量是属于哪种变量
            if(f->locals.count(identname))
                var = f->locals[identname];
            else
                var = f->params_var[identname];

            //push arr 获取数组偏移量
            AsmGen::GenAddr(var);
            AsmGen::Load();
            AsmGen::Push();

            //push index 计算索引
            this->index->asmgen(rt,ctx);
            AsmGen::Push();

            //call arr_get(arr,index)
            Internal::arr_get();
            return;
        }
    }
    //没找到 数组变量 抛出异常 exit退出
    parse_err("AsmError: index-expr use of undefined variable %s at line %d col %d\n",identname.c_str(),line,column);
}

/**
 * 函数调用求值
 * @param rt
 * @param ctx
 * @return
 */
void  FunCallExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    Debug("FunCallExpr: parsing... package:%s func:%s",package.c_str(),funcname.c_str());
    //gp 通用寄存器个数统计
    //fp 浮点数寄存器个数统计
    int gp = 0, fp = 0;

    //判断是否有可变参数
    bool have_variadic = false;
    Function* cfunc = AsmGen::currentFunc;
    for(auto arg : args){
        if (typeid(*arg) == typeid(IdentExpr) && cfunc){
            IdentExpr* var = dynamic_cast<IdentExpr*>(arg);
            if(auto res = cfunc->params_var.find(var->identname) ; res != cfunc->params_var.end()){
                IdentExpr* var2  = res->second;
                if(var2->is_variadic)
                    have_variadic = true;
            }
        }
    }
    //如果没有加包名 就默认加上当前包名进行调用
    std::string realfuncname = this->package + "." + funcname;
    if(!is_pkgcall)
        realfuncname = cfunc->parser->getpkgname() + "." + this->funcname;

    //判断是否是进行外部函数调用
    bool is_extern = false;
    if(this->package == "_"){
        realfuncname = cfunc->parser->getpkgname() + "." + this->funcname;
        is_extern = true;
    }

    //函数查找
    if(auto* func = rt->getFunc(realfuncname,is_extern); func != nullptr)
    {

        //只会进行提示，现在默认已实现不足6个参数会默认置0
        if(func->params.size() != this->args.size())
            Debug("ArgumentError: expects %d arguments but got %d\n",(int)func->params.size(),(int)this->args.size());

        int stack_args = AsmGen::Push_arg(rt,ctx,args,func->is_variadic,funcname);

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
 * @param rt
 * @param ctx
 * @return
 */
void  AssignExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){

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
    if(typeid(*lhs) == typeid(IdentExpr)){
        IdentExpr* varExpr = dynamic_cast<IdentExpr*>(lhs);

        //1. 这个变量可能是函数参数变量，非本地变量
        if(f->params_var.count(varExpr->identname))
            varExpr = f->params_var[varExpr->identname];
        else
            varExpr = f->locals[varExpr->identname];
        //这个变量一开始可能没有被注册过 需要手动注册到context中
        (ctx.back())->createVar(varExpr->identname,varExpr);

        //f->locals 保存了本地变量的 唯一偏移量，所以需要通过name 来找到对应的 变量
        AsmGen::GenAddr(varExpr);
        //注意这里传入的是变量栈地址非 lhs的值
        AsmGen::Push();

        //对运算符右值求值
        this->rhs->asmgen(rt,ctx);
        AsmGen::Push();
        //运算需要调用统一的方法
        Internal::call_operator(this->opt,"unary_operator");

        return;
    //索引赋值  a[0] = 1
    // arr_updateone(arr,index,var)
    }else if(typeid(*lhs) == typeid(IndexExpr))
    {
        std::string identname = dynamic_cast<IndexExpr*>(lhs)->identname;
        IdentExpr* varExpr;
        //1. 这个变量可能是函数参数变量，非本地变量
        if(f->params_var.count(identname))
            varExpr = f->params_var[identname];
        else
            varExpr = f->locals[identname];
        if(!varExpr)
            parse_err("SyntaxError: not find variable %s at line %d, %col\n", identname.c_str(),line,column);
        //这个变量一开始可能没有被注册过 需要手动注册到context中
        (ctx.back())->createVar(varExpr->identname,varExpr);

        //push arr 获取数组偏移量
        AsmGen::GenAddr(varExpr);
        AsmGen::Load();
        AsmGen::Push();

        //push index 计算索引
        IndexExpr* index= dynamic_cast<IndexExpr*>(lhs);
        if(!index->index) {
            rhs->asmgen(rt,ctx);
            AsmGen::Push();

            Internal::arr_pushone();
            AsmGen::Pop("%rdi");
           return;
        }

        index->index->asmgen(rt,ctx);
        AsmGen::Push();

        rhs->asmgen(rt,ctx);
        AsmGen::Push();

        //call arr_updateone(arr,index,var)
        Internal::arr_update();
        return;
    }
    parse_err("SyntaxError: can not assign to %s at line %d, %col\n", typeid(lhs).name(),line,column);
}

/**
 * 二元运算符求值
 * @param rt
 * @param ctx
 * @return
 */
void  BinaryExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
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
    this->lhs->asmgen(rt,ctx);
    AsmGen::Push();

    //对运算符右值求值
    this->rhs->asmgen(rt,ctx);
    AsmGen::Push();

    //运算需要调用统一的方法
    Internal::call_operator(this->opt,"binary_operator");
}
/**
 * TODO: 只实现了 llvm编译的new
 * 针对结构体的变量定义
 * b = new Http
 * @param rt
 * @param ctx
 * @return
 */
void  NewExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{

}
/**
 *
 * TODO: asm struct
 * @param rt
 * @param ctx
 * @return
 */
void  MemberExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
}
/**
 * TODO: asm struct call
 * @param rt
 * @param ctx
 * @return
 */
void  MemberCallExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    Debug("membercall : ")
}

