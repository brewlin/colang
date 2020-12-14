#include "Parser.h"
#include <fstream>
#include "Utils.h"
#include "AsmGen.h"
#include "Package.h"

void Parser::asmgen()
{    
    std::ofstream out(asmfile);
    AsmGen::out = &out;
    if(out.fail()){
        parse_err("genrate assembly file failed package:%s file:%s",pkg->package.c_str(),
        filename.c_str());
    }
    AsmGen::parser = this;
    AsmGen::writeln(".data");
    //1 计算变量的栈偏移量
    AsmGen::funcs_offsets();
    AsmGen::classs_offsets();
    //2 注册全局 var
    AsmGen::registerVars();
    //3 注册全局 string
    AsmGen::registerStrings();

    AsmGen::writeln(".text");
    //    AsmGen::writeln("  .file %d \"%s\"",fileno,filepath.c_str());
    if(package == "main"){
        //register main
        AsmGen::registerMain();
    }
    //4 注册 函数信息
    AsmGen::registerFuncs();
    //5 注册 对象
    AsmGen::registerObjects();
    AsmGen::parser = nullptr;


    out.close();
    AsmGen::out = nullptr;

}