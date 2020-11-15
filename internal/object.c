#include "CoreValue.h"



//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
CoreValue* newobject(int type,long data)
{
    CoreValue* ret = malloc(sizeof(CoreValue));
    switch (type){
        case Int:
            ret->type = Int;
            ret->interger = (int)data;
            break;
        case Double:
        case String:
            ret->type = String;
            ret->string = (char*)data;
        case Bool:
        case Char:
        case Null:
        case Array:
        default:
            ret->type = Null;
    }
    return ret;
}
