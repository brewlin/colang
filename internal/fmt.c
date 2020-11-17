#include "CoreValue.h"


int println(CoreValue* str,CoreValue* arg1,CoreValue* arg2)
{
    printf(str->string,arg1->string,arg2->interger);
    return 1;
}
