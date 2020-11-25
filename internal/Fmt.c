#include <string.h>
#include <stdio.h>
#include "Value.h"
#include <stdarg.h>
#include <stdio.h>

int println(Value *count,...){

    va_list ap;
    int i, total;
    Value* var;
    va_start (ap, count);

    total = (int)count->data;

    for (i = 0; i < total; i++){
        var = va_arg (ap, Value*);
        switch (var->type){
            case Int:
            case Double:
            case Bool:
                printf("%ld\t",(long)var->data);
                break;
            case String:
                printf("%s\t",var->data);
                break;
            default:
                printf("undefine\t");
        }
    }
    printf("\n");

    va_end (ap);
    return total;

}