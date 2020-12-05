/**
 *@Author brewlin
 *@Date 2020/9/2 0002 下午 3:23
 *@Version 1.0
 **/
#include "asm/AsmGen.h"
#include "Log.h"

int print_help () {
    fprintf(stderr,
            "usage: ./co [options] file.  可用的选项:\n"
            "  run      编译成汇编后进行链接生成二进制可执行文件直接运行\n"
            "  -s       编译为X64汇编文件\n"
            "  -llvm    通过llvm编译为汇编文件\n"
            "  -print   打印ast节点\n"
    );
    return 0;
}
/**
 * @param argv
 */
int llvmgen(char* argv[])
{
    Debug("llvm generate");
    std::cout << "not finish llvm yet" <<std::endl;
//    Compiler c(argv[2]);
//    c.execute();
//    c.printIR();
//    c.bin("./main.o");
    return 0;
}
/**
 * @param argv
 */
int asmgen(char* argv[],bool run = false)
{
    Debug("asm generate");
    AsmGen gen(argv[2]);
    gen.execute();
    if(run){
        system("gcc -g *.s -L./internal -linternal -L./gc -lgc");
        system("./a.out");
    }
    return 0;
}
int print_ast(char* argv[]){
    Parser p(argv[2], nullptr,"main");
    p.printToken();
    return 0;
}

int main(int argc,char* argv[])
{
    if (argc < 3) return print_help();

    if (!strcmp(argv[1], "run"))
        return asmgen(argv,true);

    if (!strcmp(argv[1], "-s"))
        return asmgen(argv,false);

    if (!strcmp(argv[1], "-llvm"))
        return llvmgen(argv);

    if (!strcmp(argv[1], "-print"))
        return print_ast(argv);

    return print_help();

}



