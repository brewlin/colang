```
struct http
{
    post
    get
    func request(){
        println("ok")
    }
}

```

```
struct  : KW_STRUCT
http    : structname
{       : TK_LBRACE
post    : varname
func    : TK_FUNC
request : funcname
(       : TK_LPAREN
)       : TK_RPAREN
{       : TK_LBRACE 
println(: FunCallExpr
"ok"    : StringExpr
)       : TK_RPAREN
}       : TK_RBRACE
}       : TK_RBRACE


```
