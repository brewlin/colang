package main

import fmt

func test(b){
    if(b){
        fmt.sprintf("OK",b)
    }else{
        fmt.sprintf("Error",b)
    }
    return 2
}
func main(){
    a = 1
    b = test(a)
    fmt.sprintf("test=%d\n",a)
}