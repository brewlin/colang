<p>
<img alt="GitHub" src="https://img.shields.io/github/license/brewlin/colang">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/brewlin/colang">
</p>

Colang是一种编程语言，旨在创造一种动态语法的静态编译语言
```asciidoc
co      [options] file.co        
    -s    file  ast -> asm       编译.co代码 生成.s汇编文件
    -run  file  ast -> asm       gcc编译后链接glic生成可执行程序
    -p    file                   打印token
cas     [options] file.s        
    -c    file.s  -> file.o      编译.s自定义汇编语言,翻译机器码并生成.o elf文件
    -p    path path...           批量扫描目录编译.s文件生成.o elf文件
    -print                       打印token
cld     [options|file.o...] 
    -p    path ... -> a.out      指定多个目录,自动扫描所有.0文件进行链接生成可执行程序
    file.o  ...-> a.out          指定多个file.o进行链接    
```
## progress
更多语法测试用例在`/tests`目录下，包含了各种数据结构、运算、gc、demo测试

- [x] compiler
  - [x] run
  - [x] -s  
  - [x] 兼容GNU `as` 汇编器，
- [x] asmer 
  - [x] -c -p
  - [x] 兼容GNU assembly 汇编语法，
  - [x] 兼容GNU `ld` 链接器，
  - [ ] 兼容GNU `.bss .rodata`段
- [x] linker 
  - [x] -p 指定扫描目录进行链接
  - [x] 取消`glic`依赖,链接独立运行库生成可执行文件
  - [ ] 兼容GNU `.bss .rodata`段
- [x] gc
    - [x] 完成python的内存分配器+标记清除式GC
    - [ ] 优化 `> 256 bytes`的大内存gc
    - [ ] 优化采用 `golang`的多线程内存分配 + 增量式三色标记gc
  
## env & install & tests 
`NOTICE`:environment install first
```asciidoc
> gcc -v
  gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04) 
> cmake -version
  cmake version 3.10.2
> git clone https://github.com/brewlin/colang.git & cd colang/tests
> cmake ../ & make 
> sudo make install
```
compile|run source code
```
> gcc -c /usr/local/lib/coasm/*.s
> co  -s rt_os_gc.co
> cas -p .
> cld -p .
> chmod 777 a.out 
> ./a.out
```
docker test
```asciidoc
> docker build . -t brewlin/colang
> docker run -it brewlin/colang /bin/bash
> cmake . & make & make install
> dos2unix tests*
> sh tests_compiler.sh
> sh tests_asmer.sh
> sh tests_linker.sh

```
## @data struct
- [x] long int
- [ ] double
- [x] string
- [x] bool
- [x] map
- [x] array
- [x] object
- [ ] closure
```
package main
import fmt
class http{
    # member
    request
    func handler(){
        fmt.println("hello world!",request,this.request)
    }
}
http::closure(){
    return func(){
        return ["arr1","arr2",3,4]
    }
}
func main(){
    a = "this is a string" #string
    fmt.println(a)
    a = 1000 # int
    fmt.println(a)
    a = ["1",2,"33",4,"some string word"] #array
    fmt.print(a[0],a[1],a[2],a[3],a[4]) #or fmt.print(a)
    b = {"sdfds":"sdfsd",1:2,"sdfds":3,"a":a} #map
    fmt.print(b["a"],b["sdfds"])
    obj = new http() #object
    obj.request = {"method":"POST"}
    obj.handler()
    cfunc = obj.closure() #closure
    fmt.println(cfunc())
    
}
```
## @keywords
- [x] func
- [x] return
- [x] package,import
- [x] if 
- [x] while,for
- [x] continue,break

```
package main
func main(){
    for(b = 1 ; b < 10 ; b += 1){
        if ( b == 2){
            fmt.println(b)
        }
        if (b == 5){
            continue
        }
        if(b == 8){
            break
        }
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

## links
- https://github.com/rui314/chibicc
- https://github.com/fanzhidongyzby/cit
- https://llvm.org/docs/tutorial/index.html
- https://github.com/brewlin/gc-learning
- https://github.com/chai2010/go-ast-book
- https://github.com/youzhonghui/MiniCRT
