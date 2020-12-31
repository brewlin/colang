#include "src/asm_parser/Parser.h"
#include <string>
#include <cstring>
#include <stdio.h>
#include "asmer/Asmer.h"

using namespace std;
using namespace asmer;


int print_help () {
    fprintf(stderr,
            "usage: ./asmer [options] file.s  可用的选项:\n"
            "  -c       翻译汇编为cpu指令，并生成可重定向elf二进制文件\n"
            "  -print   打印token\n"
    );
    return 0;
}
/**
 * @param argv
 */
int asmgen(char* argv[],bool run = false)
{
    Asmer* aer = new Asmer(argv[2]);
    aer->execute();
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

    if (!strcmp(argv[1], "-c"))
        return asmgen(argv,false);

    if (!strcmp(argv[1], "-print"))
        return print_ast(argv);

    return print_help();

}