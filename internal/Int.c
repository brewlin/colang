#include "Value.h"

long   value_int_plus(Value* lhs,Value* rhs)
{
    return (long)lhs->data + (long)rhs->data;
}

int    value_int_equal(Value* lhs,Value* rhs)
{
    return (long)lhs->data == (long)rhs->data;
}