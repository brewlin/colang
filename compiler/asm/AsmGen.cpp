/**
 *@ClassName AsmGen
 *@Author brewlin
 *@Date 2020/10/10 0010 下午 3:58
 *@Version 1.0
 **/
#include "AsmGen.h"
#include <cstdarg>
#include "../internal/Internal.h"
#include "Package.h"
#include "Parser.h"

int            AsmGen::count = 0;
Function*      AsmGen::currentFunc = nullptr;
std::ofstream* AsmGen::out = nullptr;
Parser*        AsmGen::parser = nullptr;

AsmGen::AsmGen(const std::string &filename) {

    Package* pkg = new Package("main","main");
    Parser *main_parser = new Parser(filename,pkg,"main","main");
    //main 词法解析 语法解析
    // main_parser->fileno = Parser::count ++;
    main_parser->fileno = 1;
    main_parser->parse();
    pkg->parsers[filename] = main_parser;
    Package::packages["main"] = pkg;
}
AsmGen::~AsmGen() {
}
void AsmGen::execute()
{
    //register package
    for(auto it : Package::packages){
        Package* pkg = it.second;
        pkg->asmgen();
    }
}
void AsmGen::link() {

    std::string links = "gcc -g *.s -L/usr/local/lib/colib -linternal -lgc ";
    for(auto pk : Package::packages){
        Package* pkg = pk.second;
        for(auto pr : pkg->parsers){
            Parser *p = pr.second;
            for(auto l : p->links){
                links += l;
            }
        }
    }
    system(links.c_str());
}
void AsmGen::registerMain()
{
    writeln("    .global main");
    writeln("main:");
    writeln("    push %%rbp");
    writeln("    mov %%rsp, %%rbp");
    writeln("    sub $%d, %%rsp", 0);
    Internal::call("gc_init");
    writeln("    mov %s@GOTPCREL(%%rip), %%rax", "main_main");
    writeln("    mov %%rax, %%r10");
    writeln("    mov $%d, %%rax", 0);
    writeln("    call *%%r10");
    writeln("    mov %%rbp, %%rsp");
    writeln("    pop %%rbp");
    writeln("    ret");

}
void AsmGen::funcs_offsets(Function* fn){
    //这里需要考虑闭包的情况
    if(fn->closures.size()){
        for(auto* closure : fn->closures){
            funcs_offsets(closure);
        }
    }
    //最后在计算本函数
    assign_offsets(fn);

}
void AsmGen::funcs_offsets() {
    for (auto it : parser->funcs) {
        funcs_offsets(it.second);
    }

}
void AsmGen::classs_offsets() {
    for(auto it :parser->pkg->classes){
        Class* c = it.second;
        for(auto fn : c->funcs){
            assign_offsets(fn);
        }
    }

}
/**
 * 计算
 * 函数参数栈偏移量
 * 函数局部变量栈偏移量
 * 函数栈空间大小
 */
void AsmGen::assign_offsets(Function* fn)
{
    // 如果该函数参数太多，那么超出部分将存放到栈上
    // 第一个栈参数 通过 rbp+16来定位
    // 超过6个参数后 其他参数放在调用方的栈上，而不是被调用方，那么被调用方则需要通过 offset(%rbp) 来定位
    int top = 16;
    int bottom = 0;

    int gp = 0;
    //每个变量都是一个指针 默认占8字节
    for(auto var : fn->params_order_var){
        //寄存器参数，需要存储在被调用方栈上 offset 为负
        if (gp++ < GP_MAX){
            bottom += 8;
            bottom = ALIGN_UP(bottom, 8);
            var->offset = -bottom;
        //栈参数  需要存储在调用方本地栈上
        } else{
            top = ALIGN_UP(top, 8);
            var->offset = top;
            top += 8;
        }
    }
    //如果是可变参数强制空出6个空闲栈即可
    if(fn->is_variadic){
        bottom = 48;
    }
    //计算本地变量的栈偏移量
    for(auto local:fn->locals){
        VarExpr* var = local.second;
        bottom += 8;
        bottom = ALIGN_UP(bottom, 8);
        var->offset = -bottom;
    }
    //如果是可变参数需要临时创建几个栈变量
    if(fn->is_variadic){
        bottom += 8;
        fn->size = - bottom;
        bottom += 8;
        fn->stack = - bottom;
        bottom += 8;
        fn->l_stack = - bottom;
        bottom += 8;
        fn->g_stack = - bottom;

        fn->stack_size = ALIGN_UP(bottom, 16);
    }else{
        fn->stack_size = ALIGN_UP(bottom, 16);
    }
}

//创建上下文 准备执行函数
void AsmGen::enterContext(std::deque<Context *> &ctx)
{
    auto* temp = new Context;
    ctx.push_back(temp);
}
//离开上下文
void AsmGen::leaveContext(std::deque<Context *> ctx)
{
    auto* tempContext = ctx.back();
    ctx.pop_back();
    delete tempContext;

}
/**
 * 写入 asm file
 * @param fmt
 * @param ...
 */
void AsmGen::writeln(const char *fmt, ...) {
    char buf[200];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    *out << buf << std::endl;
}
