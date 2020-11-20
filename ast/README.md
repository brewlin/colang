# 1. 内外函数区分问题
内部外部函数调用无法区分的问题
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
# 2. 外部c函数调用的交互问题
在进行外部函数调用的时候 需要传参，而当前所有参数都是复合包装的参数
```asciidoc
package time

extern int sleep(int)

func sleep(time){
    //error:time 是包装参数，需要传入原始参数
    _.sleep(time)
    
    //现在需要这样
    _.sleep(*time)
}

```
问题：导致 和 * 运算符混淆 ,目前强制规则如下:
```asciidoc
c = a * b // * 号后需要留一个空格

_.sleep(*a) // *号后直接是变量名 表示解引用

_.sleep(*1) // 注意这种有问题，任然是当做乘法使用

```
