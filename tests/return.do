package main

import fmt

func test(b){
    if(b){
        fmt.sprintln("OK",b)
    }else{
        fmt.sprintln("Error",b)
    }
    return 2
}
func main(){
    a = 1
    b = test(a)
    fmt.sprintln("test=%d\n",a)
}