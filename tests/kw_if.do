package main

import fmt
import os

func main(){
    a = 1
    if(a == 1){
        a = 10
        fmt.sprintln("OK\n")
    }else{
        fmt.sprintln("OK\n")
        os.exit(1)
        a = 5
    }

}

