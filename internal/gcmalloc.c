#include "Value.h"
#include "String.h"
#include "Array.h"
#include "Map.h"

//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
Value* newobject(int type,void* data)
{
    Value* ret = gc_malloc(sizeof(Value));
    switch (type){
        case Int:
            ret->type = Int;
            ret->data = data;
            break;
        case Double:
            ret->type = Double;
            ret->data = data;
            break;
        case String:
            ret->type = String;
            ret->data = stringnew((char*)data);
            break;
        case Bool:
            ret->type = Bool;
            ret->data = data;
            break;
        case Char:
            ret->type = Char;
            ret->data = data;
            break;
        case Null:
            ret->type = Null;
            ret->data = 0;
            break;
        case Array:
            ret->type = Array;
            ret->data = array_create(ARRAY_SIZE, sizeof(Value*));
            return ret;
        case Map:
            ret->type = Map;
            ret->data = map_create();
            return ret;
        default:
            ret->type = Null;
    }
    return ret;
}
/**
 * @param obj
 * @return
 */
long get_object_value(Value* obj){
    if(!obj) return 0;

    switch (obj->type){
        case Int:
        case Double:
        case Bool:
        case Char:
        case String:
        case Array:
            return (long)obj->data;
    }
    return NULL;
}