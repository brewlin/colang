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
