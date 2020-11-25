package main

import fmt
import os

func test_string()
{
    a = "stringa"
    b = "stringb"
    if(a != "stringa"){
        fmt.print("failed a == stringa ",a)
        os.exit(1)
    }
    if(b != "stringb"){
        fmt.print("failed b == stringb ",b)
        os.exit(1)
    }
    a += b

    if(a != "stringastringb"){
        fmt.print("failed a += b ",a)
        os.exit(1)
    }
    fmt.print("success string + string ",a)

}
func test_string_int(num,str){
    nstr = num + str + num
    if(nstr != "99test99"){
        fmt.println("failed num + str ",nstr)
        os.exit(1)
    }
    fmt.print("success num + str == ",nstr)
}

func main(){
    test_string()
    test_string_int(99,"test")
}
