package fmt

extern int printf(string)
extern int println(string)

func sprintf(args...){
   _.printf(*args)
}
func println(size,args...){
   _.println(args)
}
#func println(size,args...){
#    str
#    for(i = 0; i < size; i ++){
#        str += arg[0]
#    }
#    _.printf(str)
#}