#include "Package.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Parser.h"
#include <regex>
using namespace std;

namespace filesys = std::experimental::filesystem;

std::unordered_map<std::string,Package*> Package::packages;

Package::Package(string name,string path,bool multi)
    :package(name),path(path),full_package(path),genclass(false){
    if(multi){
        this->path = regex_replace(path,regex("_"),"/");
    }

}
Package::~Package(){}
bool Package::parse()
{
    Debug("found import.start parser..");

    std::string abpath = filesys::current_path();
    abpath += "/" + path;
    std::error_code ec;

    //先找当前，再去找全局
    if (!filesys::is_directory(abpath, ec)){
        //去全局目录库找
//        std::string srcpath = std::getenv("CO_SRC");
//        Debug("Parser: ENV PATH  CO_SRC:%s",srcpath.c_str());
//        if(srcpath.empty())
//            srcpath = "./";
//        abpath  = srcpath + "/pkg/" + package;
        abpath = "/usr/local/lib/copkg/" + path;
        Debug("Parser: package import:%s",abpath.c_str());
        if (!filesys::is_directory(abpath, ec)){
            parse_err("PackageError: package not exist :%s\n",abpath.c_str());
            return false;  
        }
    }

    //包名一般是一个目录，当前会遍历目录下所有的文件进行解析
    for(auto& p: filesys::directory_iterator(abpath)){
        std::error_code ec;
        if (filesys::is_regular_file(p.path(), ec)){
            std::string filepath = p.path();
            std::string ext = filepath.substr(filepath.size()-3,filepath.size() - 1);
            if(ext != ".co") continue;

            //不需要释放，在汇编生成的时候需要用到
            Parser *parser = new Parser(filepath,this,package,full_package);
            // parser->fileno = Parser::count ++;
            parser->fileno = 1;
            parser->parse();
            parsers[filepath] = parser;
        }
        if (ec)
            parse_err("SyntaxError: package import failed :%s\n",ec.message().c_str());
    }
    return true;
}

Function* Package::getFunc(const std::string &name, bool is_extern){
    for(auto it : parsers){
        Parser* parser = it.second;
        Function* ret  = parser->getFunc(name,is_extern);
        if(ret) return ret;
    }
    return nullptr;
}

/**
 * 添加一个类定义
 * @param name
 * @param f
 */
void Package::addClass(const std::string &name, Class *f)
{
    //在顶层package 需要统一管理所有的定义
    //如果之前已经有则 直接拷贝过去
    if(classes.count(name)){
        for(auto i : classes[name]->funcs)
            f->funcs.push_back(i);
    }
    classes[name] = f;
}
/**
 * record struct
 */
void Package::addStruct(const string &name, Struct *f)
{
    //在顶层package 需要统一管理所有的定义
    //如果之前已经有则 直接拷贝过去
    if(structs.count(name)){
        return;
    }
    structs[name] = f;
}
/**
 * 外部定义的函数需要增加到类里面
 */
void Package::addClassFunc(string name,Function* f)
{
    //先检查class是否存在
    if(classes.count(name)){
        //将成员函数追加进去
        classes[name]->funcs.push_back(f);
        return;
    }
    //临时创建一个class加入进去
    Class *s = new Class();
    s->name  = name;
    classes.insert(make_pair(name,s));
}
/**
 * 检查是否存在该类
 * @param name
 * @return
 */
bool Package::hasClass(const std::string &name)
{
    return classes.count(name) == 1;
}

VarExpr*  Package::getGlobalVar(const std::string &name){
    for(auto it : parsers){
        Parser* parser = it.second;
        if(parser->gvars.count(name)){
            return parser->gvars[name];
        }
    }
    return nullptr;
}
/**
 * 获取一个Class
 * @param name
 * @return
 */
Class* Package::getClass(const std::string &name)
{    
    if(auto f = classes.find(name);f != classes.end())
        return f->second;
    return nullptr;
}

/**
 * 检查函数是否存在
 */
bool   Package::checkClassFunc(string name,string func)
{
    if(auto f = classes.find(name);f == classes.end())
        return false;
    Class* cs = classes[name];
    for(auto var : cs->funcs){
        if(var->name == func)
            return true;
    }
    return false;
}
