#include <stdio.h>
#include "CoreValue.h"

//enum ValueType { Int,Double,String,Bool,Char,Null,Array};
int isTrue(CoreValue* cond){
    switch (cond->type){
        case Int:
            return cond->interger >= 0;
        case Double:
            return cond->long_interger >= 0;
        case String:
            return cond->string != NULL;
        case Bool:
            return cond->boolean;
        case Char:
            return cond->cchar != 0;
        case Null:
            return 0;
        default:
            return 0;
    }
}

