/**
 *@Author brewlin
 *@Date 2020/9/2 0002 下午 3:23
 *@Version 1.0
 **/
#include "asm/AsmGen.h"
#include "Log.h"

int print_help () {
    fprintf(stderr,
            "usage: ./do [options] file.  可用的选项:\n"
            "  -s       直接将ast转为asm汇编\n"
            "  -llvm    通过llvm将ast转为ams汇编\n"
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
//    Compiler c(argv[2]);
//    c.execute();
//    c.printIR();
//    c.bin("./main.o");
    return 0;
}
/**
 * @param argv
 */
int asmgen(char* argv[])
{
    Debug("asm generate");
    AsmGen gen(argv[2]);
    gen.execute();
    return 0;
}
int print_ast(char* argv[]){
    Parser::printLex(argv[2]);
    return 0;
}

int main(int argc,char* argv[])
{
    if (argc < 3) return print_help();

    if (!strcmp(argv[1], "-s"))
        return asmgen(argv);

    if (!strcmp(argv[1], "-llvm"))
        return llvmgen(argv);

    if (!strcmp(argv[1], "-print"))
        return print_ast(argv);

    return print_help();

}



