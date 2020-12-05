#include "Package.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Parser.h"

namespace filesys = std::experimental::filesystem;

Package::Package(Runtime* rt,std::string name):package(name){

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
        std::string srcpath = std::getenv("CO_SRC");
        Debug("Parser: ENV PATH  CO_SRC:%s",srcpath.c_str());
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
            Parser *parser = new Parser(filepath,package);
            parser->parse();
            parsers[filepath] = parser;
        }
        if (ec)
            parse_err("SyntaxError: package import failed :%s\n",ec.message().c_str());
    }
    return true;
}

/**
 * 添加一个函数
 * @param name
 * @param f
 */
void Package::addFunc(const std::string &name, Function *f)
{
    //函数名是 包名 + 函数名
    std::string realfuncname = f->parser->getpkgname() + "." + name;
    if(f->isExtern)
        extern_funcs.insert(std::make_pair(realfuncname,f));
    else
        funcs.insert(std::make_pair(realfuncname,f));
}
/**
 * 检查是否存在该函数
 * @param name
 * @return
 */
bool Package::hasFunc(const std::string &name, bool is_extern)
{
    if(is_extern)
        return extern_funcs.count(name) == 1;
    else
        return funcs.count(name) == 1;
}
/**
 * 获取一个func
 * @param name
 * @return
 */
Function* Package::getFunc(const std::string &name, bool is_extern)
{
    if(is_extern){
        if(auto f = extern_funcs.find(name);f != funcs.end())
            return f->second;
    }else{
        if(auto f = funcs.find(name);f != funcs.end())
            return f->second;
    }
    return nullptr;
}


/**
 * 添加一个结构体
 * @param name
 * @param f
 */
void Package::addStruct(const std::string &name, Struct *f)
{
    structs.insert(std::make_pair(name,f));
}
/**
 * 检查是否存在该结构体
 * @param name
 * @return
 */
bool Package::hasStruct(const std::string &name)
{
    return structs.count(name) == 1;
}
/**
 * 获取一个Struct
 * @param name
 * @return
 */
Struct* Package::getStruct(const std::string &name)
{
    if(auto f = structs.find(name);f != structs.end())
        return f->second;
    return nullptr;
}
