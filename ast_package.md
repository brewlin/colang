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