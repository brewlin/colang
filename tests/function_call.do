import iostream

func test(b){
    if(b){
        println("OK",b)
    }else{
        println("Error",b)
    }
    return 22
}
func equal_6(a,b,c,d,e,f){
    println("equal_6:\n")
    println("res:%d %d %d %d %d %d \n",a,b,c,d,e,f)
}
func over_6(a,b,c,d,e,f,h,i,j)
{
    println("over_6:\n")
    println("res:%d %d %d %d %d %d %d %d %d\n",a,b,c,d,e,f,h,i,j)
}
func main(){
    a = 1
    c = test(a)
    println("res:%d\n",c)
    equal_6(1,2,3,4,5,6)

    over_6(1,2,3,4,5,6,7,8,9)
}