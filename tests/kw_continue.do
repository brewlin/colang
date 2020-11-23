package main

import fmt

func test_continue(){
    a = 3
    while(a){
        a = 0
        continue
        fmt.sprintf("continue a=%d\n",a)
    }
}


func main(){
    test_continue()
}