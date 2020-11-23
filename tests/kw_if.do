package main

import fmt
import os

func main(){
    a = 1
    if(a == 1){
        fmt.sprintf("OK\n")
        if(a != 10){
            fmt.sprintf("OK\n")
        }else{
            fmt.sprintf("failed \n")
            os.exit(1)
        }
    }else{
        fmt.sprintf("OK\n")
        os.exit(1)
    }

}

