/*
 * @author brewlin
 * @date   2020/9/1
 */
#ifndef LANG_AST_H
#define LANG_AST_H

#include "do.h"
#include <string>
#include "Token.h"

struct Ast{
    explicit Ast(int line,int column):line(line),column(column){}
    virtual ~Ast() = default;
    virtual std::string toString()
    {
        return "AstNode()";
    }

    int line   = -1;
    int column = -1;
};

std::string getTokenString(Token tk);

#endif //LANG_AST_H
