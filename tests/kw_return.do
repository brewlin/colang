package main

import fmt
import os

func test_int(b){
    fmt.sprintf("test int return  %d \n",b)
    if(b != 1)
        fmt.sprintf("Error %d\n",b)
        os.exit(1)
    }
    return 2
}
func test_string(str){
    fmt.sprintf("test string return  %s \n",str)
    return str + "return"
}
func main(){
    a = 1
    b = test_int(a)
    if(b != 2){
        fmt.sprintf("Error %d\n",b)
        os.exit(1)
    }
    fmt.sprintf("test int return success ret:%d\n",b)

    if(a != 1){
        fmt.sprintf("Error %d\n",a)
        os.exit(1)
    }

    str = test_string("str-")
    if(str != "str-return"){
        fmt.sprintf("Error %s\n",str)
        os.exit(1)
    }
    fmt.sprintf("test string return success ret:%s\n",str)
}