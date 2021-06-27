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

class Package {
public:
    explicit  Package(std::string package,std::string path,bool multi = false);
    ~Package();
    bool      parse();
    void      asmgen();
    Function* getFunc(const std::string &name, bool is_extern);
    VarExpr*  getGlobalVar(const std::string &name);

public:
    //map[filepath + name] = parser
    std::unordered_map<std::string,Parser*> parsers;
	std::string package;    
    std::string path;
    std::string full_package;

public:
    static std::unordered_map<std::string,Package*> packages;
};


#endif //CO_LANG_PACKAGE_H
