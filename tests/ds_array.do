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
    fmt.print("array_get success",":",a)

}
func test_array_update()
{
    a = [1,2,3,5,6]
    if(a[0] != 1){
        fmt.println("a[0] != 1 failed")
        os.exit(1)
    }
    a[0] = "sdfds"
    if(a[0] != "sdfds"){
        fmt.println("a[0] != sdfds failed")
        os.exit(1)
    }
    a[1] = 1000
    if(a[1] != 1000){
        fmt.println("a[1] != 1000 failed")
        os.exit(1)
    }
    fmt.print("array_update success",":",a)
}

func test_array_add(){
    a   = []
    a[] = 1
    if(a[0] != 1){
        fmt.println("a[0] != 0 failed")
        os.exit(1)
    }
    a[] = "sdfs"
    if(a[1] != "sdfs"){
        fmt.println("a[1] != sdfs failed")
        os.exit(1)
    }
    a[] = "---"
    if(a[2] != "---"){
        fmt.println("a[2] != --- failed")
        os.exit(1)
    }
    fmt.print("array_add success",":",a)
}

func main(){
    test_array_index()
    test_array_update()
    test_array_add()
}
