/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "CoreValue.h"
CoreValue* value_plus(CoreValue* lhs,CoreValue* rhs) {
    CoreValue* result = (CoreValue*)gc_malloc(sizeof(CoreValue));
    if (lhs->type == Int)
    {
        switch (rhs->type){
            case Int:
            case Bool:
            case Double:
                result->type = Int;
                result->data = lhs->data + rhs->data;
                return result;
        }
        result->type = Int;
        result->data = lhs->data + rhs->data;
    }
    exit(1);
}
CoreValue* value_equal(CoreValue* lhs,CoreValue* rhs) {
    CoreValue* result = (CoreValue*)gc_malloc(sizeof(CoreValue));
    result->type = Bool;
    result->data = 0;
    //直接比较相同则返回 true
    if(lhs->data == rhs->data){
        result->data = 1;
        return result;
    }
    if (lhs->type == Int && rhs->type == Int){
        if(lhs->data == rhs->data)
            result->data = 1;
        return result;
    }
    return result;
}
