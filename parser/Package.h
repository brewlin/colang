#ifndef CO_LANG_PACKAGE_H
#define CO_LANG_PACKAGE_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "Ast.h"
#include <memory>
#include <unordered_map>
#include "Utils.h"
#include <vector>
#include <cassert>
#include "Runtime.h"
#include "Expression.h"
#include "Statement.h"
#include <cstdlib>

struct Function;
struct Block;
class  Parser;

class Package {
public:
    explicit  Package(std::string package);
    ~Package();
    bool      parse();
    void      asmgen();

    void      addFunc(const std::string &name, Function *f);
    bool      hasFunc(const std::string &name, bool is_extern);
    Function* getFunc(const std::string &name, bool is_extern);
    void      addStruct(const std::string &name, Struct *f);
    bool      hasStruct(const std::string &name);
    Struct*   getStruct(const std::string &name);
private:
    //map[filepath + name] = parser
    std::unordered_map<std::string,Parser*> parsers;
	Runtime* rt;
	std::string package;    
    //存储结构体定义
    std::unordered_map<std::string,Struct*>    structs;
    //全局变量
    std::unordered_map<std::string,VarExpr*>   gvars;
    //存储全局函数
    std::unordered_map<std::string,Function*>  funcs;
    std::unordered_map<std::string,Function*>  extern_funcs;
    //保存全局 静态字符串
    std::vector<StringExpr*>                   strs;

};


#endif //CO_LANG_PACKAGE_H
