package main

import fmt
import os

# 测试 int +=
func test_int2_add()
{
    fmt.sprintf("test int- add agn\n")
    a = 10
    b = 20
    a += b
    if(a == 30){
        fmt.sprintf("test %d + %d add agn ok\n",a,b)
    }else{
        fmt.sprintf("test %d + %d failed\n",a,b)
        os.exit(1)
    }
    fmt.sprintf("test %d + %d add agn ok\n",a,b)

    c += b
    if(c != 20){
        fmt.sprintf("test %d += %d add agn failed\n",c,b)
        os.exit(1)
    }
    fmt.sprintf("test %d += %d add agn success\n",c,b)
}
func test_string2_add(){
    fmt.sprintf("test string- add agn\n")
    a = "variable-a "
    b = "variable-b "
    a += b
    if(a == "variable-a variable-b "){
        fmt.sprintf("test string-string add agn ok\n")
    }else{
        fmt.sprintf("test string-string add agn failed\n")
        os.exit(1)
    }
    c += b
    if(c == "variable-b "){
        fmt.sprintf("test string-int add agn ok\n")
    }else{
        fmt.sprintf("test string-int add agn failed %s\n",c)
        os.exit(1)
    }

}

func main(){
    test_int2_add()
    test_string2_add()
}

