/**
 *@ClassName AsmGenFunc
 *@Author brewlin
 *@Date 2020/10/12 0012 下午 2:26
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Log.h"
#include "Block.h"


/**
 *
 */
void AsmGen::registerFuncs()
{
    Debug("register functions")
    for(Function* &f:rt->order_funcs){
        currentFunc = f;
        CreateFunction(f,rt,ctx);
        currentFunc = nullptr;
    }

}
/**
 * 注册fn
 * @param f
 */
void AsmGen::CreateFunction(Function *fn, Runtime *rt, std::deque<Context *> ctx)
{
    //extern 不需要 翻译
    if(fn->isExtern) return;
    Debug("create function :%s",fn->name.c_str())

    //定义函数块 名
    writeln("  .globl %s", fn->name.c_str());
    writeln("  .text");
    writeln("  .type %s, @function", fn->name.c_str());
    writeln("%s:", fn->name.c_str());

    //标记函数 start
    //保存rbp栈帧
    writeln("  push %%rbp");
    writeln("  mov %%rsp, %%rbp");
    writeln("  sub $%d, %%rsp", fn->stack_size);
//    保存当前rsp
//    writeln("  mov %%rsp, %d(%%rbp)", -16);

    //不管多少个参数，先把寄存器参数保存到栈在上再说
    for (int i = 0; i < 6; ++i)
        Store_gp(i, -8*(i+1), 8);
//    int gp = 0, fp = 0;
//    for(auto var:fn->params_order_var){
//        //保存参数到栈上，如果偏移量大于0 表示异常，因为通过bp来索引会影响其他函数栈参数
//        //默认 int long 8字节
//        //这里将函数参数保存栈上
//        //栈参数是保存在调用方的，所以这里不需要存储调用方的栈参数
//        if (var->offset > 0)
//            continue;
//        Store_gp(gp++, var->offset, 8);
//    }



    //如果没有block则为函数声明
    if(fn->block)
    {
        //创建一个新的上下文链
        std::deque<Context*> funcCtxChain;
        //进入新的上下文
        enterContext(funcCtxChain);
        auto* funcCtx = funcCtxChain.back();
        funcCtx->cur_funcname = fn->name;

        for(auto arg : fn->params_order_var){
            //将实参值放入新的上下文中 创建变量
            funcCtx->createVar(arg->identname,arg);
        }
        //接下来就是注册 block块
        for(auto& stmt : fn->block->stmts){
            //TODO: 处理返回值
            stmt->asmgen(rt,funcCtxChain);
        }
        leaveContext(funcCtxChain);
    }
    if(fn->name == "main")
        writeln("  mov $0, %%rax");

    // Epilogue
    writeln(".L.return.%s:", fn->name.c_str());
    writeln("  mov %%rbp, %%rsp");
    writeln("  pop %%rbp");
    writeln("  ret");
}