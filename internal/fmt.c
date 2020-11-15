#include "CoreValue.h"

int println(CoreValue* str,CoreValue* arg1,CoreValue* arg2)
{
    printf(str->string,arg1->interger,arg2->string);
    return 1;
}
