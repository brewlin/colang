package main

import fmt
import os

# 测试两个int 类型数据的比较
func test_int_greater_equal_than()
{
    fmt.sprintf("test int greaterthan...\n")

    if( 10 >= 20){
        fmt.sprintf("test 10 >= 20 failed...\n")
        os.exit(1)
    }else{
        fmt.sprintf("test 10 >= 20 success...\n")
    }
    a = 30
    b = 20
    if( a >= b){
        fmt.sprintf("test %d >= %d sucess...\n",a,b)
    }else{
        fmt.sprintf("test %d >= %d failed...\n",a,b)
        os.exit(1)
    }
    if( 10 >= 10){
        fmt.sprintf("test 10 >= 10 success...\n")
    }else{
        fmt.sprintf("test 10 >= 10 failed...\n")
        os.exit(1)
    }
    fmt.sprintf("test int greater than success...\n")
}
# 测试字符串和字符串的比较
# 测试字符串和数字的比较
func test_string_greater_equal_than(){
    fmt.sprintf("test string greaterthan...\n")

    a = "abc"
    b = "ab"
    if(a >= b){
        fmt.sprintf("test %s > %s success...\n",a,b)
    }else{
        fmt.sprintf("test %s > %s failed...\n",b,a)
        os.exit(1)
    }
    b = "ac"
    if(b >= a){
        fmt.sprintf("test %s > %s success...\n",b,a)
    }else{
        fmt.sprintf("test %s > %s failed...\n",b,a)
        os.exit(1)
    }

    a = "abc"
    b = 10
    c = a >= b
    if(c == 0){
        fmt.sprintf("test abc > 10 success...\n")
    }else{
        fmt.sprintf("test abc > 10 failed...\n")
        os.exit(1)
    }

    c = b >= a
    if(c == 0){
        fmt.sprintf("test 10 > abc success...\n")
    }else{
        fmt.sprintf("test 10 > abc failed...\n")
        os.exit(1)
    }

}
# 测试大于等于
func main(){
    test_int_greater_equal_than()
    test_string_greater_equal_than()
}

