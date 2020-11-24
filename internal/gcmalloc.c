#include "Value.h"
#include "String.h"



//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
Value* newobject(int type,long data)
{
    Value* ret = malloc(sizeof(Value));
    switch (type){
        case Int:
            ret->type = Int;
            ret->data = (int)data;
            break;
        case Double:
            ret->type = Double;
            ret->data = (long)data;
            break;
        case String:
            ret->type = String;
            ret->data = stringnew((char*)data);
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
long get_object_value(Value* obj){
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