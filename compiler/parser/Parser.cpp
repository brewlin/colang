/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Parser.h"
#include "Block.h"
#include "Log.h"

using namespace std;

int Parser::count = 1;

/**
 * 解析 脚本文件
 * @param filename
 */
Parser::Parser(const string &filepath,Package* pkg,string package,string full_package)
:pkg(pkg),
//clear
currentFunc(nullptr),
package(package),
filepath(filepath)
{
    std::string fullname = filepath.substr(filepath.find_last_of('/')+1);
    filename = fullname.substr(0,fullname.size() - 3);
    asmfile  = filename + ".s";
    if(package != "main")
        asmfile  = "co_" + package + "_" + asmfile;
    this->full_package = full_package;
    //scanner
    scanner = new Scanner(filepath);
    //记录一下本身包名的映射
    import[package] = full_package;
    //fix 本地匿名访问当前package
    import[""]  = full_package;
}
Parser::~Parser()
{
    delete scanner;
}

/**
 * @param rt
 */
void Parser::parse()
{
    //第一行必须得是包名
    scanner->scan();
    parsePackageDef();

    if(scanner->curToken == TK_EOF) return;
    do
    {
        switch(scanner->curToken)
        {
            case KW_FUNC:{
                //import 引入文件解析
                //解析函数定义
                auto* f = parseFuncDef();
                this->addFunc(f->name,f);
                break;
            }
            case KW_EXTERN:{
                //解析外部函数申明 extern与interpret没关系，只影响 irgen
                auto *f = parseExternDef();
                this->addFunc(f->name, f);
                break;
            }
            case KW_EXTRA:{
                //解析 注释里面特别指明的附加信息，如link： 链接外部库等
                parseExtra();
                break;
            }
            case KW_IMPORT:{
		        //解析import
			    parseImportDef();
                break;
            }
            case KW_CLASS:{
		        //解析结构体类定义
                parseClassDef();
                break;
            }
            case KW_STRUCT:{
                //解析struct内存结构
                parseStructDef();
                break;
            }
            default:{
                //解析全局定义: global var, class::func
                parseGlobalDef();
            }
        }
    }while(scanner->curToken != TK_EOF);
}
/**
 * @return string package name
 */
std::string Parser::getpkgname()
{
    //这里返回完整的包名
    return this->full_package;
    // return package;
}

void Parser::check(bool check)
{
    if(!check){
        parse_err("parse: found token error token:%s line:%d column:%d\n",
        getTokenString(scanner->curToken).c_str(),scanner->line,scanner->column);
        exit(-1);
    }
}

