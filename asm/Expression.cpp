/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "Expression.h"
#include "Interpreter.h"
#include "AsmGen.h"
#include "Log.h"
#include "Internal.h"

//===---------------------------------------------------------------------===//
// 计算所有的表达式 并返回一个 Value 结构，

Value NullExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    return Value(Null);
}
Value BoolExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    return Value(Bool,this->literal);
}
Value CharExpr::asmgen(Runtime* rt,
                         std::deque<Context*> ctx) {
    return Value(Char, this->literal);
}

Value IntExpr::asmgen(Runtime* rt, std::deque<Context*> ctx) {
    AsmGen::writeln("  mov $%ld, %%rax", this->literal);
    return Value(Int, this->literal);
}

Value DoubleExpr::asmgen(Runtime* rt,
                           std::deque<Context*> ctx) {
    return Value(Double, this->literal);
}

Value StringExpr::asmgen(Runtime* rt,
                           std::deque<Context*> ctx) {
    AsmGen::writeln("  lea %s(%%rip), %%rax", name.c_str());
    return Value(String, this->literal);
}
/**
 * 数组变量生成
 * @param rt
 * @param ctx
 * @return
 */
Value ArrayExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    std::vector<Value> elements;
    //数组内的元素可能类型不同 如 [1,"2","3"] 所以需要遍历生成Value 存入vector中
    for(auto& e: this->literal)
        //遍历调用 asmgen 生成 Value
        elements.push_back(e->asmgen(rt,ctx));
    return Value(Array,elements);
}
/**
 * load 变量
 * 1 计算偏移量
 * 2 加载变量
 * @param rt
 * @param ctx
 * @return
 */
Value IdentExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){

    //变量遍历表 看是否存在
    for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
        auto* ctx = *p;
        if(auto* var = ctx->getVar(this->identname);var != nullptr){

            Function* f = AsmGen::currentFunc;
            //地址生成
            if(f->locals[identname] == nullptr){
                AsmGen::GenAddr(f->params_var[identname]);
            }else{
                AsmGen::GenAddr(f->locals[identname]);
            }
//            AsmGen::Load(var->value.type);
            AsmGen::Load(Int);
            //["a",123] return 123
            return Value(Null);
//            return var->value;
        }
    }
    panic("RuntimeError:use of undefined variable %s at line %d co %d\n",
          identname.c_str(),this->line,this->column);
}
/**
 * 索引 数组
 * @param rt a[1]
 * @param ctx
 * @return
 */
Value IndexExpr::asmgen(Runtime* rt,std::deque<Context*> ctx) {
    for(auto p = ctx.crbegin();p != ctx.crend(); ++p){
        //查看 a 变量是否存在 var 对应的应该是一个  vector
        if(auto* var = (*p)->getVar(this->identname); var != nullptr){
            //将当前index 转换为  Value
            auto idx = this->index->asmgen(rt,ctx);
            //判断 索引是不是 int类型
            if(!idx.isType<Int>())
                panic("TypeError:expects index is int type at line %d col %d\n",line,column);
            //判断有没有越界 index >= size(var) var->value是一个vector类型
            if(idx.cast<int>() >= var->value.cast<std::vector<Value>>().size())
                panic("IndexError: index %d out of range at line %d col %d\n",idx.cast<int>(),line,column);
            //返回数组索引对应的那个 值  也就是 return a[1]
            return var->value.cast<std::vector<Value>>()[idx.cast<int>()];
        }
    }
    //没找到 数组变量 抛出异常 exit退出
    panic("RuntimeError:use of undefined variable %s aat line %d col %d\n",identname.c_str(),line,column);
}

/**
 * 赋值运算符 求值
 * @param rt
 * @param ctx
 * @return
 */
Value AssignExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
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
        Value rhs = this->rhs->asmgen(rt,ctx);
        //运算需要调用统一的方法
        Internal::CallOperator(this->opt);
        //执行结果存储
        AsmGen::Store(rhs.type);

        std::string identname = varExpr->identname;
        for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
            //查看变量表是否存在该 变量
            if(auto* var = (*p)->getVar(identname); var != nullptr){
                //进行赋值操作 并返回右值
                var->value = Interpreter::assignSwitch(this->opt,var->value,rhs);
                return rhs;
            }
        }

        //说明不存在该变量 则需要重新定义
        (ctx.back())->createVar(identname,rhs);
        return rhs;
        //可能是索引运算如: a[1] = 123
    }else if(typeid(*lhs) == typeid(IndexExpr))
    {
        Value rhs = this->rhs->asmgen(rt,ctx);
        std::string identname = dynamic_cast<IndexExpr*>(lhs)->identname;
        Value   index     = dynamic_cast<IndexExpr*>(lhs)->index->asmgen(rt,ctx);
        //如果索引不是int则panic : a["1"];
        if(!index.isType<Int>())
            panic("TypeError: expects index is int type to variable %s at line %d co %d\n",identname.c_str(),line,column);
        //通过全局变量表 找到该数组
        for(auto p = ctx.crbegin(); p != ctx.crend(); ++p){
            //如果该变量不是 array 则抛出类型错误，不能对非数组变量进行索引操作
            if(auto * var = (*p)->getVar(identname); var != nullptr){
                if(!var->value.isType<Array>())
                    panic("TypeError: expects array type of vaiable %s  ate line %d %col\n",identname.c_str(),line,column);
                //转换为 vector 操作
                auto&& temp = var->value.cast<std::vector<Value>>();
                temp[index.cast<int>()] = Interpreter::assignSwitch(
                        this->opt,temp[index.cast<int>()],rhs);
                //右值转移数据
                var->value.data = std::move(temp);
                return rhs;
            }
        }
        //创建一个变量
        (ctx.back()->createVar(identname,rhs));
        return rhs;
        //其他情况 非法
    }else{
        panic("SyntaxError: can not assign to %s at line %d, %col\n", typeid(lhs).name(),line,column);
    }
}

/**
 * 函数调用求值
 * @param rt
 * @param ctx
 * @return
 */
Value FunCallExpr::asmgen(Runtime* rt,std::deque<Context*> ctx){
    int gp = 0, fp = 0;
    //用户定义函数: 通过函数名查找该函数
    if(auto* func = rt->getFunc(this->funcname); func != nullptr){
        //TODO: 函数默认传参
        if(func->params.size() != this->args.size())
            Debug("ArgumentError: expects %d arguments but got %d\n",func->params.size(),this->args.size());
        int stack_args = AsmGen::Push_arg(rt,ctx,args);
        //加载函数名
        // 将函数名的地址保存到 rax中
        for(auto arg : args){
            if (gp < GP_MAX)
                AsmGen::Pop(AsmGen::argreg64[gp++]);
        }

        AsmGen::writeln("  mov %s@GOTPCREL(%%rip), %%rax", funcname.c_str());
        AsmGen::writeln("  mov %%rax, %%r10");
        AsmGen::writeln("  mov $%d, %%rax", fp);
        AsmGen::writeln("  call *%%r10");
        AsmGen::writeln("  add $%d, %%rsp", stack_args * 8);
        return Value(Null);

    }
    panic(
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
Value BinaryExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    Value lhs = this->lhs ? this->lhs->asmgen(rt,ctx) : Value(Null);
    Value rhs = this->rhs ? this->rhs->asmgen(rt,ctx) : Value(Null);

    Token  opt = this->opt;
    //lhs != null & rhs == null 一元求值
    if(!lhs.isType<Null>() && rhs.isType<Null>())
        return Interpreter::calcUnaryExpr(lhs,opt,line,column);
    //二元求值
    return Interpreter::calcBinaryExpr(lhs,opt,rhs,line,column);
}
/**
 * TODO: 只实现了 编译的new 未实现 interpreter的new
 * 针对结构体的变量定义
 * b = new Http
 * @param rt
 * @param ctx
 * @return
 */
Value NewExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    return Value(String,type);
}
/**
 *
 * TODO: 待实现interprter 的结构体
 * @param rt
 * @param ctx
 * @return
 */
Value MemberExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    return Value(String,varname);
}
/**
 * TODO: 未实现interpreter 的结构体内部函数调用
 * @param rt
 * @param ctx
 * @return
 */
Value MemberCallExpr::asmgen(Runtime* rt,std::deque<Context*> ctx)
{
    return Value(String,varname);
}

