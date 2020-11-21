#include "CoreValue.h"



//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
CoreValue* newobject(int type,long data)
{
    CoreValue* ret = malloc(sizeof(CoreValue));
    switch (type){
        case Int:
            ret->type = Int;
            ret->data = (int)data;
            break;
        case Double:
        case String:
            ret->type = String;
            ret->data = (long)data;
            break;
        case Bool:
            ret->type = Bool;
            ret->data = (int)data;
            break;
        case Char:
            ret->type = Char;
            ret->data = (int)data;
            break;
        case Null:
            ret->type = Null;
            ret->data = 0;
            break;
        case Array:
            return ret;
        default:
            ret->type = Null;
    }
    return ret;
}
long get_object_value(CoreValue* obj){
    if(!obj) return NULL;

    switch (obj->type){
        case Int:
        case Double:
        case Bool:
        case Char:
        case String:
            return obj->data;
    }
    return NULL;
}