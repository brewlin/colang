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
#include "Expression.h"
#include "Statement.h"
#include <cstdlib>

struct Function;
struct Block;
class  Parser;

using namespace std;

class Package {
public:
    explicit  Package(std::string package,std::string path,bool multi = false);
    ~Package();
    bool      parse();
    void      asmgen();
    Function* getFunc(const std::string &name, bool is_extern);
    VarExpr*  getGlobalVar(const std::string &name);

    void      addStruct(const string &name, Struct *f);

    void      addClass(const string &name, Class *f);
    bool      hasClass(const string &name);
    void      addClassFunc(string name,Function* f);
    bool      checkClassFunc(string name,string func);
    Class*    getClass(const string &name);

public:
    //map[filepath + name] = parser
    std::unordered_map<std::string,Parser*> parsers;
	std::string package;    
    std::string path;
    std::string full_package;
    //在codegen阶段 多个parser是属于同一个packge下，只需要执行一次class codgen
    bool        genclass;

    std::unordered_map<std::string,Class*>  classes;
    std::unordered_map<std::string,Struct*> structs;

public:
    static std::unordered_map<std::string,Package*> packages;
};


#endif //CO_LANG_PACKAGE_H
