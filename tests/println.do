package main

import fmt


func println1(args...){
  printf(args)
}
func main(){
    a = -1323
    if(a){
        println1("a is negative not should be here %d %s\n",a,"wrong")
    }else{
        println1("ok %d %s\n",a,"it's clear")
    }
}

