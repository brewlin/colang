#include "Package.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Parser.h"

namespace filesys = std::experimental::filesystem;

Package::Package(Runtime* rt,std::string name):rt(rt),package(name){

}
Package::~Package(){

}

bool Package::parse()
{
    Debug("found import.start parser..");

    std::string abpath = filesys::current_path();
    abpath += "/" + package;
    std::error_code ec;

    //先找当前，再去找全局
    if (!filesys::is_directory(abpath, ec)){
        //去全局目录库找
        std::string srcpath = std::getenv("DO_SRC");
        Debug("Parser: ENV PATH  DO_SRC:%s",srcpath.c_str());
        if(srcpath.empty())
            srcpath = "./";
        abpath  = srcpath + "/" + package;
        Debug("Parser: package import:%s",abpath.c_str());
        if (!filesys::is_directory(abpath, ec))
            return false;  
    }

    //包名一般是一个目录，当前会遍历目录下所有的文件进行解析
    for(auto& p: filesys::directory_iterator(abpath)){
        std::error_code ec;
        if (filesys::is_regular_file(p.path(), ec)){
            std::string filepath = p.path();
            std::string ext = filepath.substr(filepath.size()-3,filepath.size() - 1);
            if(ext != ".co") continue;

            //不需要释放，在汇编生成的时候需要用到
            Parser *parser = new Parser(filepath,rt,package);
            parser->parse();
            parsers[filepath] = parser;
        }
        if (ec)
            parse_err("SyntaxError: package import failed :%s\n",ec.message().c_str());
    }
    return true;
}