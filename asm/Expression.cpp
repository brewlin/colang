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
//    std::vector<Value> elements;
//    //数组内的元素可能类型不同 如 [1,"2","3"] 所以需要遍历生成Value 存入vector中
//    for(auto& e: this->literal)
//        //遍历调用 asmgen 生成 Value
//        elements.push_back(e->asmgen(rt,ctx));

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
            //地址生成
            if(f->locals[identname] == nullptr)
                AsmGen::GenAddr(f->params_var[identname]);
            else
                AsmGen::GenAddr(f->locals[identname]);
            AsmGen::Load();
            return;
        }
    }
    parse_err("RuntimeError:use of undefined variable %s at line %d co %d\n",
          identname.c_str(),this->line,this->column);
}
/**
 * 索引 数组
 * @param rt a[1]
 * @param ctx
 * @return
 */
void  IndexExpr::asmgen(Runtime* rt,std::deque<Context*> ctx) {
    //没找到 数组变量 抛出异常 exit退出
    parse_err("RuntimeError:use of undefined variable %s aat line %d col %d\n",identname.c_str(),line,column);
}

/**
 * 赋值运算符 求值
 * @param rt
 * @param ctx
 * @return
 */
void  AssignExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    //如果左值是一个标识符 表达式: a = 13;
    if(typeid(*lhs) == typeid(IdentExpr)){
        IdentExpr* varExpr = dynamic_cast<IdentExpr*>(lhs);
        //进行赋值 和 变量定义
        Function* f = AsmGen::currentFunc;
        //f->locals 保存了本地变量的 唯一偏移量，所以需要通过name 来找到对应的 变量
        AsmGen::GenAddr(f->locals[varExpr->identname]);
        //保存rax寄存器的值 因为下面右值计算的时候会用到rax寄存器
        AsmGen::Push();
        //对运算符右值求值
        this->rhs->asmgen(rt,ctx);
        //运算需要调用统一的方法
        Internal::CallOperator(this->opt);
        //执行结果存储
        AsmGen::Store();

        std::string identname = varExpr->identname;
        //说明不存在该变量 则需要重新定义
        (ctx.back())->createVar(identname,varExpr);
        return;
        //可能是索引运算如: a[1] = 123
    }
    parse_err("SyntaxError: can not assign to %s at line %d, %col\n", typeid(lhs).name(),line,column);
}

/**
 * 函数调用求值
 * @param rt
 * @param ctx
 * @return
 */
void  FunCallExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    int gp = 0, fp = 0;

    bool have_depointer = false;
    Function* cfunc = AsmGen::currentFunc;
    for(auto arg : args){
        if (typeid(*arg) == typeid(IdentExpr) && cfunc){
            IdentExpr* var = dynamic_cast<IdentExpr*>(arg);
            if(auto res = cfunc->params_var.find(var->identname) ; res != cfunc->params_var.end()){
                IdentExpr* var2  = res->second;
                if(var2->is_multi)
                    have_depointer = true;
            }
        }
    }
    //用户定义函数: 通过函数名查找该函数
    if(auto* func = rt->getFunc(this->funcname); func != nullptr){

        //TODO: 函数默认传参
        if(func->params.size() != this->args.size())
            Debug("ArgumentError: expects %d arguments but got %d\n",func->params.size(),this->args.size());

        int stack_args = AsmGen::Push_arg(rt,ctx,args,func->is_multi);

        //把参数寄存器给填满了
        if(cfunc && cfunc->is_multi && have_depointer)
        {
           //do nothing
        }else{
            for (int i = 0; i < GP_MAX; ++i)
                AsmGen::Pop(AsmGen::argreg64[gp++]);
        }

        AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        AsmGen::writeln("  mov %%rax, %%r10");
        AsmGen::writeln("  mov $%d, %%rax", fp);
        AsmGen::writeln("  call *%%r10");


        //如果当前函数调用存在解引用可变参数则需要动态计算函数栈上移的大小
        if(AsmGen::currentFunc && AsmGen::currentFunc->is_multi && have_depointer)
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
            "RuntimeError: can not find function definition of %s in both "
            "built-in "
            "functions and user defined functions\n",
            this->funcname.c_str());
}
/**
 * 二元运算符求值
 * @param rt
 * @param ctx
 * @return
 */
void  BinaryExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
//    void  lhs = this->lhs ? this->lhs->asmgen(rt,ctx) : void (Null);
//    void  rhs = this->rhs ? this->rhs->asmgen(rt,ctx) : void (Null);
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

}

