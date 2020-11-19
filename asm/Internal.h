//
// Created by root on 2020/11/15.
//

#ifndef LANG_INTERNAL_H
#define LANG_INTERNAL_H

#include "Ast.h"
#include <string>

class Internal
{
public:
    static void CallOperator(Token opt);
    static void newobject(int type,long data);
    static void gc_malloc();
    static void isTrue();
    static void get_object_value();
    static void call(std::string funcname);
};
#endif //LANG_INTERNAL_H
