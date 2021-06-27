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
    :package(name),path(path),full_package(path){
    if(multi){
        this->path = regex_replace(path,regex("_"),"/");
    }

}
Package::~Package(){

}

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

VarExpr*  Package::getGlobalVar(const std::string &name){
    for(auto it : parsers){
        Parser* parser = it.second;
        if(parser->gvars.count(name)){
            return parser->gvars[name];
        }
    }
    return nullptr;
}