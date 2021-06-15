/**
 *@ClassName AsmGenFunc
 *@Author brewlin
 *@Date 2020/10/12 0012 下午 2:26
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "Log.h"
#include "Block.h"
#include "Parser.h"

void AsmGen::registerFunc(Function* fn)
{
    //这里需要先处理闭包函数
    if(fn->closures.size())
    {
        for(auto* closure : fn->closures){
            std::string funcname = "func_" + std::to_string(Function::closureidx ++);
            closure->receiver->varname = fn->parser->getpkgname() + "_" + funcname;
            closure->parser = fn->parser;
            closure->name   = funcname;
            //递归去创建
            registerFunc(closure);
        }
    }
    //最后创建当前函数
    currentFunc = fn;
    CreateFunction(fn);
    currentFunc = nullptr;

}

/**
 * 扫描所有的parser下的函数并依次生成汇编码
 */
void AsmGen::registerFuncs()
{
    Debug("register functions")
    int sign = 0;
    for(auto p :parser->funcs){
        registerFunc(p.second);
    }
}
/**
 * 注册fn
 * @param f
 */
void AsmGen::CreateFunction(Function *fn,Class* c)
{
    //extern 不需要 翻译
    if(fn->isExtern) return;
    std::string funcname = fn->parser->getpkgname() + "_" + fn->name;
    //成员函数
    if(c){
        funcname = fn->parser->getpkgname() + "_" + c->name + "_" + fn->name;
    }
    Debug("create function :%s",funcname.c_str())

    //定义函数块 名
    writeln(".global %s", funcname.c_str());
    writeln("%s:", funcname.c_str());

    //标记函数 start
    //保存rbp栈帧
    writeln("    push %%rbp");
    writeln("    mov %%rsp, %%rbp");
    writeln("    sub $%d, %%rsp", fn->stack_size);
//    保存当前rsp
//    writeln("    mov %%rsp, %d(%%rbp)", -16);

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
        funcCtx->cur_funcname = funcname;

        for(auto arg : fn->params_order_var){
            //将实参值放入新的上下文中 创建变量
            funcCtx->createVar(arg->varname,arg);
        }
        //接下来就是注册 block块
        for(auto& stmt : fn->block->stmts){
            stmt->asmgen(funcCtxChain);
        }
        leaveContext(funcCtxChain);
    }
    if(fn->name == "main")
        writeln("    mov $0, %%rax");

    writeln("L.return.%s:", funcname.c_str());
    writeln("    mov %%rbp, %%rsp");
    writeln("    pop %%rbp");
    writeln("    ret");
}