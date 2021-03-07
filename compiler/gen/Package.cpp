#include "Package.h"
#include "Parser.h"

void Package::asmgen()
{
    for(auto it : parsers){
        Parser *p = it.second;
        p->asmgen();
    }
}