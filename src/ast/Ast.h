/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef CO_LANG_AST_H
#define CO_LANG_AST_H

#include "colang.h"
#include <string>
#include "Token.h"

struct Ast{
    explicit Ast(int line,int column):line(line),column(column){}
    virtual ~Ast() = default;
    virtual std::string toString()
    {
        return "Ast()";
    }

    int line   = -1;
    int column = -1;
};

std::string getTokenString(Token tk);

#endif //CO_LANG_AST_H
