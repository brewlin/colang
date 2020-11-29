package main

import fmt
import time
import os

func test_while(){
    a = 4
    while(a != 2){
        fmt.sprintf("a=%d\n",a)
        time.sleep(1)
        a = a - 1
    }
    if(a != 2){
        fmt.sprintf("failed a:%d should be 2 \n",a)
        os.exit(1)
    }
    fmt.sprintf("success a:%d should be 2 \n",a)
}


func main(){
    test_while()
}