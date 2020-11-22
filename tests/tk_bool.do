package main

import fmt
import os

func main(){
    fmt.sprintln("bool test\n")

    # 测试 bool 赋值  和 istrue判断
    isbool = true
    if(isbool){
        fmt.sprintln("bool test ok\n")
    }else{
        fmt.sprintln("bool test failed\n")
        os.exit(1)
    }

    # 测试 bool 赋值  和 istrue判断
    isbool = false
    if(isbool){
        fmt.sprintln("bool test failed\n")
        os.exit(1)
    }else{
        fmt.sprintln("bool test ok\n")
    }


}
