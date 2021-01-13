#include "minicrt.h"

void assert(int ret){
    if(!ret){
        printf("assert failed\n");
        exit(1);
    }
}
void __ctype_b_loc(){}
void __stack_chk_fail(){}
