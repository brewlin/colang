#include "src/asm_parser/Parser.h"
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;
using namespace asmer;


int print_help () {
    fprintf(stderr,
            "usage: ./asmer [options] file.s  可用的选项:\n"
            "  -s       翻译汇编为机器指令，并生成可重定向elf二进制文件\n"
            "  -print   打印token\n"
    );
    return 0;
}
/**
 * @param argv
 */
int asmgen(char* argv[],bool run = false)
{
    return 0;
}
int print_ast(char* argv[]){
    Parser p(argv[2]);
    p.printToken();
    return 0;
}

int main(int argc,char* argv[])
{
    if (argc < 3) return print_help();

    if (!strcmp(argv[1], "-s"))
        return asmgen(argv,false);

    if (!strcmp(argv[1], "-print"))
        return print_ast(argv);

    return print_help();

}