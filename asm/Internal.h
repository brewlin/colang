//
// Created by root on 2020/11/15.
//

#ifndef LANG_INTERNAL_H
#define LANG_INTERNAL_H

#include "Ast.h"

class Internal
{
public:
    static void CallOperator(Token opt);
    static void newobject(int type,long data);
    static void gc_malloc();
};
#endif //LANG_INTERNAL_H
