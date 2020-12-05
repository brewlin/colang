#include "Package.cpp"
#include "Parser.cpp"

void Package::asmgen()
{
    for(auto it : parsers){
        Parser *p = it.sencond;
        p->asmgen();
    }
)
}