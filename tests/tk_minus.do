package main

import fmt
import os

func test_int(){
    a = 10
    if(a != 10){
        os.exit(1)
    }
    a = a - 1
    if(a != 9){
        fmt.sprintf("test int minus %d != 9 failed\n",a)
        os.exit(1)
    }
    fmt.sprintf("test int minus %d != 9 success\n",a)
}
# 对字符串做运算不做任何操作
func test_string(){
    a = "abc"
    a = a - 1
    if(a != "abc"){
        fmt.sprintf("test string minus %s != abc failed\n",a)
        os.exit(1)
    }
    fmt.sprintf("test string minus %s != abc success\n",a)
}

func test_intp(str){
    if(str != "test"){
        fmt.sprintf("test string minus %s != abc failed\n",str)
        os.exit(1)
    }
    fmt.sprintf("test string minus %s != abc success\n",str)
}

# 注意目前 减运算 需要留空格
# a = b - 1  correct
# a = b -1   wrong
func main(){
    test_int()
    test_string()
    test_intp("test" -1)
}