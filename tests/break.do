package main

import fmt

func test_while_break(){
    a = 10
    while(a){
        fmt.sprintln("break\n")
        break
    }
}
func break_double(){
    b = 1
    while(b){
        c = 1
        fmt.sprintln("outside\n")
        while(c){
            fmt.sprintln("inside\n")
            break
        }
        break
    }
}

func main(){
    test_while_break()
    break_double()
}