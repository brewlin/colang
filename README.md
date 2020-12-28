<p>
<img alt="GitHub" src="https://img.shields.io/github/license/brewlin/colang">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/brewlin/colang">
</p>

Colang是一种编程语言，旨在创造一种动态语法的静态编译语言
```asciidoc
./colang [options] file.co
    run   file  ast -> asm       编译为汇编-链接生成可执行程序自动执行
    -s    file  ast -> asm       编译为汇编
./asmer [options] file.s
    -c    file.s  -> file.o     解析编译汇编文件生成.o 可重定向elf
    -p                           打印token
```
- [x] compiler
  - [x] run 采用gcc进行汇编和链接glibc
  - [x] -s  生成.s汇编文件
- [ ] asmer 
  - [x] -c 自定义汇编，翻译机器指令生成elf可重定向
  - [x] 兼容GNU assembly 汇编语法，
  - [ ] 兼容GNU `as` 汇编器，
- [ ] linker 
  - [ ] 链接生成可执行文件
  - [ ] 兼容GNU `ld` 链接器
# env & install
```asciidoc
> uname -a
Linux ubuntu 4.4.0-157-generic #185-Ubuntu SMP Tue Jul 23 09:17:01 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
> gcc -v
gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 
> git clone https://github.com/brewlin/colang.git
> cd colang/tests
> export CO_SRC=/path/to/colang/runtime
> cmake .. & make
> dos2unix auto_tests.sh & sh auto_tests.sh


```
# @progress
更多语法测试用例在`/tests`目录下，包含了各种数据结构、运算、gc、demo测试
## @GC
- [x] 完成python的内存分配器+标记清除式GC
- [ ] 优化 `> 256 bytes`的大内存gc
- [ ] 优化采用 `golang`的多线程内存分配 + 增量式三色标记gc
## @data struct
- [x] long int
- [ ] double
- [x] string
- [x] bool
- [x] map
- [x] array
- [x] object
```
package main
import fmt

class http{
    # member
    request
    # func
    func handler(){
        fmt.println("hello world!")
        fmt.println(this.request)
    }
}
func main(){
    a = "this is a string"
    fmt.println(a)
    a = 1000
    fmt.println(a)
    a = ["1",2,"33",4,"some string word"]
    fmt.print(a[0],a[1],a[2],a[3],a[4])
    //or fmt.print(a)
    b = {"sdfds":"sdfsd",1:2,"sdfds":3,"a":a}
    fmt.print(b["a"],b["sdfds"])
    obj = new http()
    obj.request = {"method":"POST"}
    obj.handler()
    
}
```
## @keywords
- [x] func
- [x] return
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

## @operators
- [x] `+  and +=` 
- [x] `-  and -=`
- [x] `*  and *=`
- [x] `\  and \=`
- [x] `<< and <<=`
- [x] `>> and >>=`
- [x] `&  and &=`
- [x] `|  and |=`
- [x] `|| and &&`
- [x] `>  and >=`
- [x] `<  and <=`
- [x] `== and !=`