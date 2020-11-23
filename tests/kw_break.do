package main

import fmt

func test_while_break(){
    a = 10
    while(a){
        if(a == 5){
            fmt.sprintf("should break %d\n",a)
            break
        }
        a = a - 1
        fmt.sprintf("break %d\n",a)
    }
}
func break_double(){
    b = 1
    while(b){
        c = 1
        fmt.sprintf("outside\n")
        while(c){
            fmt.sprintf("inside\n")
            break
        }
        break
    }
}

func main(){
    test_while_break()
    #break_double()
}