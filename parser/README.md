1. 内部外部函数调用无法区分的问题
```asciidoc
package time

extern int sleep(int)

func sleep(){

}
func xxx(){
    //这个就不知道是调用当前包的函数
    //还是调用外部函数
    sleep()
    
    //现在通过下划线(_.) 来表示外部函数的调用

```
