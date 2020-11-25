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
    static void call_operator(Token opt,std::string name);
    static void newobject(int type,long data);
    static void gc_malloc();
    static void isTrue();
    static void get_object_value();
    static void call(std::string funcname);

    //array
    static void arr_pushone();
    static void arr_update();
    static void arr_get();

};
#endif //LANG_INTERNAL_H
