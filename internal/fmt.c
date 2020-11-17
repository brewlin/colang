#include "CoreValue.h"


int println(CoreValue* str,CoreValue* a1,CoreValue* a2)
{
    printf(str->string,a1->interger,a2->interger);
    return 1;
}
