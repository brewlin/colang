package main

import fmt

func test(b){
    if(b){
        fmt.println("OK",b)
    }else{
        fmt.println("Error",b)
    }
    return 2
}
func main(){
    a = 1
    b = test(a)
    fmt.println("test=%d\n",a)
}