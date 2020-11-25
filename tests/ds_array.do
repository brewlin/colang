package main

import fmt
import os

func test_array_index()
{
    a = [1,"2","3333","this is 4"]
    if(a[0] != 1){
        fmt.println("a[0] == 1 failed")
        os.exit(1)
    }
    if(a[1] != "2"){
        fmt.println("a[1] == 2 failed")
        os.exit(1)
    }
    if(a[2] != "3333"){
        fmt.println("a[2] == 3333 failed")
        os.exit(1)
    }
    if(a[3] != "this is 4"){
        fmt.println("a[3] == this is 4 failed")
        os.exit(1)
    }
    fmt.println(a[0],a[1],a[2],a[3])

}

func main(){
    test_array_index()
}
