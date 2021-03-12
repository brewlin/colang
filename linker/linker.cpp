#include <iostream>
#include <string>
#include <cstring>
#include "link/Linker.h"
#include <experimental/filesystem>

namespace filesys = std::experimental::filesystem;

using namespace std;

int print_help () {
    fprintf(stderr,
            "usage: ./co-linker [options|file.o...] \n"
            "  -p       指定扫描目录下所有.0文件进行链接生成可执行程序\n"
            "  file.o   ... 手动指定多个file.o进行链接\n"
    );
    return 0;
}
/**
 *
 * @param argv
 * @return
 */
int link(int argc,char *argv[])
{
    Linker linker;
    string outfile = "a.out";
    for (int i = 1; i < argc;) {
        string obj = argv[i++];
        //添加目标文件
        linker.addElf(obj);
    }
    //开始链接
    linker.link(outfile);
    return 0;
}
/**
 *
 * @param argc
 * @param argv
 * @return
 */
int scan(int argc,char *argv[])
{
    Linker linker;
    string outfile = "a.out";
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
                if(filename.substr(filename.size() - 2) == ".o"){
                    //添加目标文件
                    linker.addElf(filename);
                }
            }
        }
    }
    //开始链接
    linker.link(outfile);
    return 0;
}
/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc,char* argv[])
{
    if (argc < 3) return print_help();

    //scan all the files
    if (!strcmp(argv[1], "-p"))
        return scan(argc,argv);

    return link(argc,argv);
}