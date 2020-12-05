#include "Parser.h"
#include <fstream>
#include "Utils.h"
#include "AsmGen.h"

void Parser::asmgen()
{    
    std::string fullname = filename + ".s";
    std::ofstream out(fullname,ios::app);
    AsmGen::out = &out;
    if(out.fail()){
        parser_s("genrate assembly file failed package:%s file:%s",pkg->package.c_str(),
        filename.c_str());
    }
    


    out.close();
    AsmGen::out = nullptr;

}