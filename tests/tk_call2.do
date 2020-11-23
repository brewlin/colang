package main

import fmt
import os


func test(b){
    if(b == 1){
        fmt.sprintf("OK%d\n",b)
        b = 100
    }else{
        fmt.sprintf("Error %d\n",b)
        os.exit(1)
    }
    return 22
}

func main(){
    a = 1
    c = test(a)
    if(c == 22){}
    else{
        fmt.sprintf("res:%d\n != 22 failed",c)
        os.exit(1)
    }

}