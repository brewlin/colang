## 关于测试
批量测试单元测试用例
```asciidoc
> cd colang
> dos2unix auto*
> sh auto_tests_compiler.sh
> sh auto_tests_asmer.sh
> sh auto_tests_linker.sh
```
- @data struct 测试
`ds_`开头的文件为 数据结构 测试
- @keyword 测试
`kw_`开头的文件为 keyword 关键字测试

- @token语法测试
`tk_`开头的文件为 token 语法测试
- @运行库测试
`rt_`开头的文件为 运行时库 后面跟库名的单元测试
## 语法规则
### 1. 内外函数区分问题
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
### 2. 外部c函数调用的交互问题
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
### 3.附加信息语法
```asm
package ***
#:link ***
``` 
通过`#:link` 后面可以待链接信息，指定链接静态库

## 运算规则
1. 同一个包名下的函数默认编译时需要加上前缀
```asciidoc
package fmt 
func println(){
}

= > 翻译为汇编后

fmt.println:
    ret

```

2. 同一个包下的函数内部调用默认加上 前缀
```asciidoc
package fmt

func main(){
    println()
}

=> 翻译为汇编后

main:
    call fmt.println    

```

3. 不同包的函数外部调用需要自己加上前缀


## 数据类型操作
### @string 字符串操作
- `string + string`
```asciidoc
a = "abc-"
b = "abc"
c = a + b // c = "abc-abc"

d = "abc-" + "abc" //d = "abc-abc"

```
- `string + int`
```asciidoc
a = "abc-"
b = 1000
c = a + b // c = "abc-1000"

d = "abc-" + 1000 //d = "abc-1000"
```
- `string * string`
```asciidoc
a = "abc"
b = "def"
c = a * b
//c == "abcdef"

```
- `string * int`
```asciidoc
a = "abc"
b = 2
c = a * b
//c == "abcabc"

```

### @int 数字操作

- `int + int`
```asciidoc
a = 1
b = 2
c = a + b 

d = 1 + 2
//c 和 d == 3
```

- `int + string`
```asciidoc
a = 1
b = "-str"
c = a + b
//c == "1-str"

```


- `int * int`
```asciidoc
a = 2
b = 3
c = a * b

d = 2 * 3
//c == d == 5

```

- `int * string`
```asciidoc
a = 2
b = "str"
c = a * b
//c == "strstr"

```
