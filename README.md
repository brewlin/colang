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
ubuntu os 16
llvm-6.0

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
- [x] int
- [ ] double
- [x] string
- [ ] map
- [ ] array
```
package main
import fmt

func main(){
    a = "this is a string"
    fmt.sprintf("str:%s\n",a)
    b = 1000
    fmt.sprintf("str:%s\n",a)
    c = 77323.088
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
- [x] +,+= 
- [x] -,-=
- [x] *,*=
- [x] \,\=
- [x] <<,<<=
- [x] >>,>>=
- [x] &,&=
- [x] |,|=
- [x] >,>=
- [x] <,<=
- [x] ==,!=