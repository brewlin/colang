package main

import fmt
import os

# 测试 int + 
func test_int2_add()
{
    fmt.sprintln("test int- add\n") 
    a = 10
    b = 20
    c = a + b
    if(c == 30){
        fmt.sprintln("test int-int add ok\n")
    }else{
        fmt.sprintln("test int-int add failed\n")
        os.exit(1)
    }
}
func test_string2_add(){
    fmt.sprintln("test string- add\n")
    a = "variable-a "
    b = "variable-b "
    c = a + b 
    if(c == "variable-a variable-b "){
        fmt.sprintln("test string- add ok\n")
    }else{
        fmt.sprintln("test string- add failed\n")
        os.exit(1)
    }

}
func main(){
    test_int2_add()
    test_string2_add()
}

