package fmt

extern int printf(string)
extern int println(string)

func sprintf(args...){
   _.printf(*args)
}
func println(size,args...){
   _.println(args)
}
