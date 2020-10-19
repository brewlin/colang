/**
 *@ClassName AsmGenFunc
 *@Author brewlin
 *@Date 2020/10/12 0012 下午 2:26
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Log.h"


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
    //保存当前rsp
    writeln("  mov %%rsp, %d(%%rbp)", -16);

    //TODO:可变参数
    int gp = 0, fp = 0;
    for(auto &param:fn->params_var){
        //默认 int long 8字节
        //这里将函数参数保存栈上
        IdentExpr* var = param.second;
        Store_gp(gp++, var->offset, 8);
    }

    //如果没有block则为函数声明
    if(fn->block){
        //接下来就是注册 block块
        for(auto& stmt : fn->block->stmts){
            //TODO: 处理返回值
            stmt->asmgen(rt,ctx);
        }
    }
    if(fn->name == "main")
        writeln("  mov $0, %%rax");

    // Epilogue
    writeln(".L.return.%s:", fn->name.c_str());
    writeln("  mov %%rbp, %%rsp");
    writeln("  pop %%rbp");
    writeln("  ret");
}