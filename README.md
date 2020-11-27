# lang
一款动态语法的静态编译器  手写汇编生成器、llvm接入示例、解析器动态执行
```asciidoc
./do [options] file
    -i    file  ast -> run       动态解析运行
    -s    file  ast -> asm       编译为汇编
    -llvm file  ast -> ir -> asm 基于llvm生成汇编

```
# env
```asciidoc
Linux ubuntu 4.4.0-157-generic #185-Ubuntu SMP Tue Jul 23 09:17:01 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux

gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 

```
# install
```asciidoc
> git clone https://github.com/brewlin/lang.git
> cd lang
> mkdir bin
> cd bin
> cmake .. & make


```

# 语法
## 数据类型
- [x] long int
- [ ] double
- [x] string
- [x] bool
- [x] map
- [x] array
```
package main
import fmt

func main(){
    a = "this is a string"
    fmt.println(a)
    a = 1000
    fmt.println(a)
    a = ["1",2,"33",4,"some string word"]
    fmt.print(a[0],a[1],a[2],a[3],a[4])
    //or fmt.print(a)
}
```
## 关键字
- [x] func,return
- [x] package,import
- [x] if 
- [x] while
- [x] continue,break

```
package main
func main(){
    a = "str"
    if(a == "str"){
    }
    b = 10
    while(b){
        if(b == 5){
            continue
        }
        if(b == 2){
            break
        }
        b -= 1
    }
}
```

## 操作符
- [x] `+  and +=` 
- [x] `-  and -=`
- [x] `*  and *=`
- [x] `\  and \=`
- [x] `<< and <<=`
- [x] `>> and >>=`
- [x] `&  and &=`
- [x] `|  and |=`
- [x] `>  and >=`
- [x] `<  and <=`
- [x] `== and !=`