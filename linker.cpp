#include <iostream>
#include <string>
#include <cstring>
#include "linker/Linker.h"
using namespace std;

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
int main(int argc,char* argv[])
{
    return link(argc,argv);
}