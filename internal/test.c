#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "help.h"

int __failed_tests = 0;
int __test_num = 0;

void main(){

   test_string();
   test_array();
   test_map();
   test_report();
}