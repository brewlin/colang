package main

import fmt

func test(b){
    if(b){
        fmt.println("OK",b)
    }else{
        fmt.println("Error",b)
    }
    return 22
}
func equal_6(a,b,c,d,e,f){
    fmt.println("equal_6:\n")
    fmt.println("res:%d %d %d %d %d %d \n",a,b,c,d,e,f)
}
func over_6(a,b,c,d,e,f,h,i,j)
{
    fmt.println("over_6:\n")
    fmt.println("res:%d %d %d %d %d %d %d %d %d\n",a,b,c,d,e,f,h,i,j)
}

func main(){
    a = 1
    c = test(a)

    fmt.println("res:%d\n",c)
    equal_6(1,2,3,4,5,6)

    over_6(1,2,3,4,5,6,7,8,9)
}