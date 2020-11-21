package main

import fmt
import os

#测试 值比较
func test_value_equal(){
    fmt.sprintln("test value equal...\n")
    if( 10 == 10){
        fmt.sprintln("test 1 == 1 sucess...\n")
    }else{
        fmt.sprintln("test 1 == 1 failed...\n")
        os.exit(1)
    }
}
#测试 变量比较
func test_variable_equal(){
    fmt.sprintln("test variable equal...\n")
    a = 10
    abc = 12
    b = 10
    if( a == b){
        fmt.sprintln("test a(10) == b(10) sucess...\n")
    }else{
        fmt.sprintln("test a(10) == b(10) failed...\n")
        os.exit(1)
    }

    b = 12
    if( a == b){
        fmt.sprintln("test a(10) == b(12) failed...\n")
        os.exit(1)
    }else{
        fmt.sprintln("test a(10) == b(12) success...\n")
    }
}

func main(){
    test_value_equal()
    test_variable_equal()
}

