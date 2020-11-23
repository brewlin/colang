package main

import fmt
import os

# 测试 int + 
func test_int2_add()
{
    fmt.sprintf("test int- add\n")
    a = 10
    b = 20
    c = a + b
    if(c == 30){
        fmt.sprintf("test int-int add ok\n")
    }else{
        fmt.sprintf("test int-int add failed\n")
        os.exit(1)
    }
}
func test_string2_add(){
    fmt.sprintf("test string- add\n")
    a = "variable-a "
    b = "variable-b "
    c = a + b 
    if(c == "variable-a variable-b "){
        fmt.sprintf("test string-string add ok\n")
    }else{
        fmt.sprintf("test string-string add failed\n")
        os.exit(1)
    }
    c = a + 10
    if(c == "variable-a 10"){
        fmt.sprintf("test string-int add ok\n")
    }else{
        fmt.sprintf("test string-int add failed %s\n",c)
        os.exit(1)
    }

}
func test_addintcall(a){
    if(a == 3){
        fmt.sprintf("test addintcall  ok 1+2=%d\n",a)
    }else{
        fmt.sprintf("test addintcall  failed\n")
        os.exit(1)
    }

}

func test_addstringcall(a){
    if(a == "test"){
        fmt.sprintf("test addstringcall  ok tes+t=%s\n",a)
    }else{
        fmt.sprintf("test addstringcall  failed\n")
        os.exit(1)
    }

}


func main(){
    test_int2_add()
    test_string2_add()
    test_addintcall(1+2)
    test_addstringcall("tes" + "t")
}

