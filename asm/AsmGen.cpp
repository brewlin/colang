/**
 *@ClassName AsmGen
 *@Author brewlin
 *@Date 2020/10/10 0010 下午 3:58
 *@Version 1.0
 **/
#include "AsmGen.h"

int AsmGen::count = 0;
Function* AsmGen::currentFunc = nullptr;
FILE *output_file;
/**
 * 写入 asm file
 * @param fmt
 * @param ...
 */
void AsmGen::writeln(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(output_file, fmt, ap);
    va_end(ap);
    fprintf(output_file, "\n");
}

AsmGen::AsmGen(const std::string &filename) {
    rt = new Runtime("main");
    p = new Parser(filename,rt);
}
AsmGen::~AsmGen() {
    delete  p;
    delete rt;
}

void AsmGen::execute()
{
    //词法解析 语法解析
    this->p->parse();
    this->ctx.push_back(new Context);


    char *buf;
    size_t buflen;
    output_file = open_memstream(&buf, &buflen);
    //1 计算变量的栈偏移量
    assign_offsets();
    //2 注册全局 string
    registerStrings();
    //3 注册 函数信息
    registerFuncs();

    fclose(output_file);
    FILE *out = fopen("./asm.s", "w");
    std::cout << buf <<std::endl;
    fwrite(buf, buflen, 1, out);
    fclose(out);
}
/**
 * 计算
 * 函数参数栈偏移量
 * 函数局部变量栈偏移量
 * 函数栈空间大小
 */
void AsmGen::assign_offsets() {
    //顺序遍历所有的 Function
    for (auto* fn : rt->order_funcs){

        // 如果该函数参数太多，那么超出部分将存放到栈上
        // 第一个栈参数 通过 rbp+16来定位
        int top = 16;
        int bottom = 0;

        int gp = 0, fp = 0;
        //TODO:假定所有参数类型为 int 8字节
        for(auto param : fn->params_var){
            IdentExpr* var = param.second;
            top = ALIGN_UP(top, 8);
            var->offset = top;
            top += 8;
        }
        //TODO: 在parser ast function时 将本地局部变量加入 fn->locals 方便计算偏移量
        // Assign offsets to pass-by-register parameters and local variables.
        for(auto local:fn->locals){
            IdentExpr* var = local.second;
            bottom += 8;
            bottom = ALIGN_UP(bottom, 8);
            var->offset = -bottom;
        }
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