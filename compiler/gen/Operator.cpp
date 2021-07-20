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
#include "OperatorHelper.h"
using namespace std;

/**
 * 赋值运算符 求值
 * @param ctx
 * @return
 */
Expression*  AssignExpr::asmgen(std::deque<Context*> ctx){

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
                return nullptr;
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
        //如果左值是一个struct，需要优化:p<header> = （expression)| int
        if(varExpr->structtype){
            OperatorHelper oh(ctx,lhs,rhs,this->opt);
            oh.var = varExpr;
            return oh.gen();
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

        return nullptr;
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
           return nullptr;
        }

        index->index->asmgen(ctx);
        AsmGen::Push();

        rhs->asmgen(ctx);
        AsmGen::Push();

        //call arr_updateone(arr,index,var)
        Internal::kv_update();
        //rm unuse 
        AsmGen::Pop("%rdi");
        return nullptr;
    }else if(typeid(*lhs) == typeid(StructMemberExpr))
    {
        OperatorHelper oh(ctx,lhs,rhs,this->opt);
        return oh.gen();
    }
    parse_err("SyntaxError: can not assign to %s at line %d, %col\n", typeid(lhs).name(),line,column);
}
/**
 * 二元运算符求值
 * @param ctx
 * @return
 */
Expression*  BinaryExpr::asmgen(std::deque<Context*> ctx)
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
    //如果左右两边有一个 结构体值则 默认进行memory 运算
    bool mhandle = false;
    VarExpr* var;
    //结构体成员访问
    if(typeid(*this->lhs) == typeid(StructMemberExpr) || typeid(*this->rhs) == typeid(StructMemberExpr))
        mhandle = true;
    //指针解引用 
    if(typeid(*this->lhs) == typeid(DelRefExpr) || typeid(*this->rhs) == typeid(DelRefExpr))
        mhandle = true;
    //变量
    if(typeid(*this->lhs) == typeid(VarExpr)){
        var = dynamic_cast<VarExpr*>(this->lhs);
        var = var->getVar(ctx);
        if(var->structtype)
            mhandle = true;
    }
    if(typeid(*this->rhs) == typeid(VarExpr)){
        var = dynamic_cast<VarExpr*>(this->rhs);
        var = var->getVar(ctx);
        if(var->structtype)
            mhandle = true;
    }
    //需要处理
    if(mhandle){
        OperatorHelper oh(ctx,lhs,rhs,this->opt);
        return oh.gen();
    }

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
Expression*  ChainExpr::asmgen(std::deque<Context*> ctx)
{
    //left codegen
    this->lhs->asmgen(ctx);
    AsmGen::Push();
    // pass %rax 中间通过rax将各个节点链接起来
    //righ codegen
    this->rhs->asmgen(ctx);
}
/**
 * 1. *var 这种是对动态变量对解引用
 * 2. *p   这种是对内存对指针访问
 * 3. 支持递归解引用  ****var
 */
Expression*  DelRefExpr::asmgen(std::deque<Context*> ctx){
    Expression* ret = this->expr->asmgen(ctx);
    //支持对变量的解引用
    if (typeid(*ret) == typeid(VarExpr)){
        VarExpr* var = dynamic_cast<VarExpr*>(ret);
        //普通变量
        if(!var->structtype){
            Internal::get_object_value(); return ret;
        }
        //对变量解引用必须是 指针类型，这里强制要求一下
        if(!var->pointer){
            parse_err("var must be pointer %s\n",this->expr->toString().c_str());
        }
        if(var->size != 1 && var->size != 2 && var->size != 4 && var->size != 8){
            parse_err("type must be [i8 - u64]:%s\n",this->expr->toString().c_str());
        }
        //获取指针指向的值
        AsmGen::Load(var->size,var->isunsigned);
        return ret;
    }else if(typeid(*ret) == typeid(StructMemberExpr)){
        StructMemberExpr* sm = dynamic_cast<StructMemberExpr*>(ret);
        Member* m = sm->ret;
        if(m == nullptr){
            parse_err("del ref can't find the struct member:%s\n",this->expr->toString().c_str());
        }
        if(typeid(*expr) != typeid(DelRefExpr)){
            //结构体现在统一返回的是地址，需要再次load
            AsmGen::Load(m);
        }
        //获取指针指向的值
        AsmGen::Load(m->size,m->isunsigned);
        return ret;
    }
    parse_err("only support del ref for expression :%s\n",this->expr->toString().c_str());
}
/**
 * &a || &p.b
 * 取地址比较特殊，不能嵌套子Expression 需要自己处理 var 和 struct的地址引用
 * TODO: &addr
 */
Expression*  AddrExpr::asmgen(std::deque<Context*> ctx){
    if(package != ""){
        //如果package 不为空
        // 1. &p<struct>.var 成员变量取地址
        VarExpr* var = Context::getVar(ctx,this->package);
        if(var != nullptr && var->structtype){
            //get member
            StructMemberExpr sm(package,line,column);
            sm.member = varname;
            sm.var    = var;
            Member* m = sm.getMember();
            if(m != nullptr){
                //获取到首地址
                AsmGen::GenAddr(var);
                //指针类型
                AsmGen::Load();
                //加载偏移量
                AsmGen::writeln("	add $%d, %%rax", m->offset);
                //如果不是出现在赋值语句中 则自动读取内存
                if(m->bitfield){
                    parse_err(
                        "AsmError: adress to bitfield error! "
                        "line:%d column:%d \n\n"
                        "expression:\n%s\n",
                        this->line,this->column,this->toString().c_str());
                }
                return this;
            }
        }

    // 2. &p.var 全局变量的直接取地址
    }
    parse_err("only support & struct.menber\n");
    return this;
    // 1. &var 变量的直接取地址
    // 4. &p<struct>  直接取地址

    // 异常情况:
    // 1. &obj.var 变量的成员变量取地址
    

}