//
// Created by root on 2020/11/15.
//

#ifndef CO_LANG_INTERNAL_H
#define CO_LANG_INTERNAL_H

#include "Ast.h"
#include <string>
#include "Token.h"
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
    static void kv_update();
    static void kv_get();

    //map
    static void map_pushone();

};
#endif //CO_LANG_INTERNAL_H
