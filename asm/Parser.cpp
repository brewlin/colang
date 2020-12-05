#include "Parser.h"
#include <fstream>
#include "Utils.h"

void Parser::asmgen()
{    
    std::string fullname = filename + ".s";
    std::ofstream out(fullname,ios::app);
    if(out.fail()){
        parser_s("genrate assembly file failed package:%s file:%s",pkg->package.c_str(),
        filename.c_str());
    }
    out<<"myid:"<<myid<<endl;
    out<<"procnum:"<<procnum<<endl;
    out.close();
    ofstream out("./log",ios::app

}