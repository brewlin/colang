/**
 *@ClassName AsmGenReg
 *@Author brewlin
 *@Date 2020/10/16 0016 上午 9:01
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Internal.h"


/**
* 加载变量 计算变量
* @param expr
*/
void AsmGen::GenAddr(IdentExpr *var)
{
    // 局部变量 的栈偏移量之前就已经计算出来了 这里只需要
    if (var->is_local) {
        writeln("  lea %d(%%rbp), %%rax", var->offset);
        return;
    }
    // 全局变量 直接根据标号来引用即可
    writeln("  lea %s(%%rip), %%rax", var->name.c_str());

}
/**
 *
 * @param type
 */
void AsmGen::Load()
{
    writeln("  mov (%%rax), %%rax");

}
/**
 * @param type
 */
void AsmGen::CreateCmp()
{
    writeln("  cmp $0, %%eax");
}
void AsmGen::PushS(const char *arg)
{
    writeln("  push %s",arg);
}
void AsmGen::Push()
{
    writeln("  push %%rax");
}
void AsmGen::Pop(const char *arg)
{
    writeln("  pop %s",arg);
}
/**
 * 加载函数调用参数，这些参数都已经作为本地变量保存在栈上了
 * 这里要做的就是将他们加载到寄存器中
 * 1. 达到6个参数则用 DI, RSI,RDX, RCX, R8 and R9 寄存器.
 * 每个参数占 8字节
 * @return
 */
int AsmGen::Push_arg(Runtime *rt,std::deque<Context *> prevCtxChain,std::vector<Expression *> &args,bool is_multi)
{
    int stack = 0, gp = 0;

    //查看当前调用函数参数里有没有可变参数
    bool current_call_have_im = false;
    //查看当前函数里是否有可变参数
    for(auto arg : args){
        if (typeid(*arg) == typeid(IdentExpr) && currentFunc){
            IdentExpr* var = dynamic_cast<IdentExpr*>(arg);
            if(auto res = currentFunc->params_var.find(var->identname) ; res != currentFunc->params_var.end()){
                IdentExpr* var2  = res->second;
                if(var2->is_multi)
                    current_call_have_im = true;
            }
        }
    }

    //说明需要对当前可变参数进行解引用
    if(currentFunc && currentFunc->is_multi && current_call_have_im)
    {
        int c = AsmGen::count++;
        //第一个参数是从 -16算起，因为-8是参数个数需要忽略
        int params = -16;
        //保存所有的寄存器
        for (int i = 0; i < 5; ++i) {
            writeln("  mov %d(%%rbp),%%rax",params);
            Internal::get_object_value();
            writeln("  mov %%rax,%s",AsmGen::argreg64[i]);
            params += -8;
        }

        writeln("  mov 16(%%rbp),%%rax");
        Internal::get_object_value();
        writeln("  mov %%rax,%%r9");

        //接下来存储栈参数

        //忽略第一个参数从第二个参数开始算起来
        //如果要读取上层的变量值 需要调用get_object_value 切记
        writeln("  mov -8(%%rbp),%%rax");
        Internal::get_object_value();

        writeln("  sub $6,%%rax");
        writeln("  mov %%rax,%d(%%rbp)",currentFunc->size);

        writeln("  mov $16,%%rax");
        writeln("  mov %%rax,%d(%%rbp)",currentFunc->stack);

//        while

        writeln("  jmp .L.while.end.%d",c);
        writeln(".L.while.%d:",c);

        //         stack = 16 + (size * 8);
        //         push(gstack(%rbp)
        //         size --;
        writeln("  mov %d(%%rbp),%%rax",currentFunc->size);
        writeln("  imul $8,%%rax");
        writeln("  add $16,%%rax");
        writeln("  mov %%rax,%d(%%rbp)",currentFunc->stack);
        writeln("  lea (%%rbp),%%rax");

        writeln("  add %d(%%rbp),%%rax",currentFunc->stack);
        writeln("  mov (%%rax),%%rax");
        Internal::get_object_value();
        writeln("  push %%rax");

        writeln("  sub $1,%d(%%rbp)",currentFunc->size);
        //while condition
        writeln(".L.while.end.%d:",c);
        writeln("  mov %d(%%rbp),%%rax",currentFunc->size);
        writeln("  cmp $0,%%rax");
        writeln("  jg  .L.while.%d",c);

    //不需要对可变参数进行解引用，顺序存储寄存器即可
    }else{
        //小于6个参数，也需要把6个参数寄存器给补齐了
        if(args.size() < 6)
            for (int i = 0; i < (6 - (int)args.size()); ++i)
                writeln("  push $0");

        //尽可能的加载跟多参数到寄存器  需要倒序
        for (int i = args.size() - 1; i >= 0; i--) {
            //栈参数
            if (gp++ >= GP_MAX) {
                stack++;
            }
            //读取每个变量到rax寄存器上
            args[i]->asmgen(rt,prevCtxChain);
            Push();
        }
        //如果是可变参数，第一个参数填充数字个数
        if(is_multi){
            stack -- ;
            Internal::newobject(Int,args.size());
//            writeln("  mov $%d,%%rax",args.size());
            Push();
        }
    }


//    if (stack % 2 == 1) {
//        writeln("  sub $8, %%rsp");
//        stack++;
//    }
    return stack;
}