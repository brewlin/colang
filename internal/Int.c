#include "Value.h"

// +
long   value_int_plus(Value* lhs,Value* rhs){
    return (long)lhs->data + (long)rhs->data;
}
// -
long   value_int_minus(Value* lhs,Value* rhs){
    return (long)lhs->data - (long)rhs->data;
}
// *
long   value_int_mul(Value* lhs,Value* rhs){
    return (long)lhs->data * (long)rhs->data;
}
// /
long   value_int_div(Value* lhs,Value* rhs){
    return (long)lhs->data / (long)rhs->data;
}
// &
long   value_int_bitand(Value* lhs,Value* rhs){
    return (long)lhs->data & (long)rhs->data;
}
// |
long   value_int_bitor(Value* lhs,Value* rhs){
    return (long)lhs->data | (long)rhs->data;
}
// <<
long   value_int_shift_left(Value* lhs,Value* rhs){
    return (long)lhs->data << (long)rhs->data;
}
// >>
long   value_int_shift_right(Value* lhs,Value* rhs){
    return (long)lhs->data >> (long)rhs->data;
}
// ==
int    value_int_equal(Value* lhs,Value* rhs,int equal){
    if(equal)
        return (long)lhs->data == (long)rhs->data;
    else
        return (long)lhs->data != (long)rhs->data;
}
// !=
int    value_int_notequal(Value* lhs,Value* rhs){
    return (long)lhs->data != (long)rhs->data;
}
// <
int    value_int_lowerthan(Value* lhs,Value* rhs,int equal){
    if(equal)
        return (long)lhs->data <= (long)rhs->data;
    else
        return (long)lhs->data < (long)rhs->data;
}
// >
int    value_int_greaterthan(Value* lhs,Value* rhs,int equal){
    if(equal)
        return (long)lhs->data >= (long)rhs->data;
    else
        return (long)lhs->data > (long)rhs->data;
}