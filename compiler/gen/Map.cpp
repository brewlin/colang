/*
 * @author brewlin
 * @date   2021/6/9
 */
#include "Expression.h"
#include "asm/AsmGen.h"
#include "Log.h"
#include "internal/Internal.h"
#include "Ast.h"
#include "Value.h"
#include "Parser.h"

/**
 * asm gen map
 * @param ctx
 */
Expression*  MapExpr::asmgen(std::deque<Context*> ctx){
    Debug("MapExpr: gen... ");
//    AsmGen::writeln("    .loc %d %d %d",AsmGen::parser->fileno,line,column);

    //new array & push array
    Internal::newobject(Map, 0);
    AsmGen::Push();

    for(auto& element: this->literal){
        //new element & push element
        element->asmgen(ctx);
        Internal::kv_update();
    }

    //pop array
    AsmGen::Pop("%rax");
}