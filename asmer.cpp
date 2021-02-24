#include "asmer/parser/Parser.h"
#include <string>
#include <cstring>
#include <stdio.h>
#include "asmer/Asmer.h"
#include <experimental/filesystem>

namespace filesys = std::experimental::filesystem;

using namespace std;
using namespace asmer;


int print_help () {
    fprintf(stderr,
            "usage: ./asmer [options] file.s  可用的选项:\n"
            "  -c *.s   翻译汇编为cpu指令，并生成可重定向elf二进制文件\n"
            "  -p ...   批量翻译汇编为cpu指令，并生成可重定向elf二进制文件\n"
            "  -print   打印token\n"
    );
    return 0;
}
/**
 * @param argv
 */
int asmgen(char* argv[])
{
    Asmer* aer = new Asmer(argv[2]);
    aer->execute();
    return 0;
}
/**
 *
 * @param argv
 * @return
 */
int asmgenpath(int argc , char* argv[])
{
    for (int i = 2 ; i < argc;) {

        string path = argv[i++];
        std::error_code ec;
        if (!filesys::is_directory(path, ec)){
            cout <<  ec.message().c_str() << endl;
            exit(1);
        }

        //包名一般是一个目录，当前会遍历目录下所有的文件进行解析
        for(auto& p: filesys::directory_iterator(path)) {
            std::error_code ec;
            if (filesys::is_regular_file(p.path(), ec)) {
                string filename = p.path();
                if(filename.substr(filename.size() - 2) == ".s"){
                    Asmer aer(filename);
                    aer.execute();
                }
            }
        }
    }
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
        return asmgen(argv);

    if (!strcmp(argv[1], "-p"))
        return asmgenpath(argc,argv);

    if (!strcmp(argv[1], "-print"))
        return print_ast(argv);

    return print_help();

}