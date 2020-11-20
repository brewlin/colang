package main

import fmt
import time

func test_while(){
    a = 3
    b = 0
    while(a){
        fmt.println("a=%d\n",a)
        time.sleep(1)
        a = 0
        b = 1
    }
    if(b){
        fmt.println("!\n")
    }
}


func main(){
    test_while()
}