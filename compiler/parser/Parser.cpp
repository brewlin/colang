/*
 * @author brewlin
 * @date   2020/9/1
 */
#include "Parser.h"
#include "Block.h"
#include "Log.h"

using namespace std;

int Parser::count = 1;

unordered_map<std::string,Token > keywords = 
{
    {"if",KW_IF},         {"else",KW_ELSE},     {"else",KW_ELSE},
    {"while", KW_WHILE},  {"for", KW_FOR},      {"false", KW_FALSE},
    {"true", KW_TRUE},    {"null", KW_NULL},    {"func", KW_FUNC},
    {"return", KW_RETURN},{"break", KW_BREAK},  {"continue", KW_CONTINUE},
    {"import", KW_IMPORT},{"extern", KW_EXTERN},{"class", KW_CLASS},
    {"new", KW_NEW},      {"go", KW_GO},        {"package", KW_PACKAGE},
    {"struct",KW_STRUCT},
};
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
    fs.open(filepath,std::ios::in);
    if(!fs.is_open()){
        parse_err("ParserError: can not open script file :%s\n",filepath.c_str());
    }
    std::string fullname = filepath.substr(filepath.find_last_of('/')+1);
    filename = fullname.substr(0,fullname.size() - 3);
    asmfile  = filename + ".s";
    if(package != "main")
        asmfile  = package + "_" + asmfile;
    this->full_package = full_package;
    //记录一下本身包名的映射
    import[package] = full_package;
}
Parser::~Parser()
{
    fs.close();
}

/**
 * @param rt
 */
void Parser::parse()
{
    //第一行必须得是包名
    scan();
    parsePackageDef();

    if(getCurrentToken() == TK_EOF) return;
    do{
        //import 引入文件解析
        //解析函数定义
        if(getCurrentToken() == KW_FUNC)
        {
            auto* f = parseFuncDef();
            this->addFunc(f->name,f);
        //解析外部函数申明 extern与interpret没关系，只影响 irgen
        } else if(getCurrentToken() == KW_EXTERN) {
            auto *f = parseExternDef();
            this->addFunc(f->name, f);
            //解析 注释里面特别指明的附加信息，如link： 链接外部库等
        } else if(getCurrentToken() == KW_EXTRA){
            parseExtra();
		//解析import
        } else if(getCurrentToken() == KW_IMPORT){
			parseImportDef();
		//解析结构体类定义
		} else if(getCurrentToken() == KW_CLASS){
            parseClassDef();
        //解析全局变量定义
        }else{
            parseGlobalDef();
        }

    }while(getCurrentToken() != TK_EOF);


}
char Parser::next() {
    column++;
    return static_cast<char>(fs.get());
}
std::string Parser::getline() {
    std::string line;
    std::getline(fs,line);
    return line;
}
char Parser::peek() {
    return static_cast<char>(fs.peek());
}
Token Parser::getPrevToken()const {
    return preToken;
}
Token Parser::getCurrentToken()const {
    return curToken;
}
std::string Parser::getCurrentLexeme()const {
    return curLex;
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
/**
 * 测试token解析
 * @param filename
 */
std::string Parser::printToken()
{
    auto  tk = get_next();
    while(std::get<0>(tk) != TK_EOF){
        std::cout << "" << getTokenString(std::get<0>(tk)) << " => " << std::get<1>(tk) << "\n";
        tk = get_next();
    }

}
