#include <stdio.h>
#include "CoreValue.h"

//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
int isTrue(CoreValue* cond){
    switch (cond->type){
        case Int:
            return cond->data >= 0;
        case Double:
            return cond->data >= 0;
        case String:
            return cond->data != NULL;
        case Bool:
            return cond->data;
        case Char:
            return cond->data != 0;
        case Null:
            return 0;
        default:
            return 0;
    }
}

