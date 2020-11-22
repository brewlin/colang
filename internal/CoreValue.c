/*
 * @author brewlin
 * @date   2020/9/6
 */
#include "CoreValue.h"
#include "string.h"
CoreValue* value_plus(CoreValue* lhs,CoreValue* rhs) {
    CoreValue* result = (CoreValue*)gc_malloc(sizeof(CoreValue));
    if (lhs->type == Int)
    {
        result->type = Int;
        switch (rhs->type){
            case Int:
            case Bool:
            case Double:
                result->type = Int;
                result->data = (int)lhs->data + (int)rhs->data;
                return result;
        }
        exit(1);
    }
    if(lhs->type == String){
        result->type = String;
        result->data = stringdup(rhs->data);
        switch(rhs->type){
            case Int:
            case Bool:
            case Double:
                exit(1);
            case String:
            result->data = stringcat(result->data,rhs->data);
            return result;
        }
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
