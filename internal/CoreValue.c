/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "CoreValue.h"
CoreValue* value_plus(CoreValue* lhs,CoreValue* rhs) {
    CoreValue* result = (CoreValue*)malloc(sizeof(CoreValue));
    if (lhs->type == Int && rhs->type == Int)
    {
        result->type = Int;
        *(int*)result->data = *(int*)lhs->data + *(int*)rhs->data;
    }
    return result;
}

