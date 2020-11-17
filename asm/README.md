# 可变参函数
```
//push_args

         
        
 int size = 8;
 int stack = 5;
 int lstack = -8;
 int gstack = 16;
 while(size > 0 ){
       if(stack < 5){
           lstack -= -8;
           push(lstack(%rbp));
       }else{
           gstack += 8;
           push(gstack(%rbp)
       }
       size --;
  }
  
   int size = 8 - 5;
   int stack = 16;
   while(size > 0 ){
         stack = 16 + (size * 8);
         push(gstack(%rbp)
         size --;
    }
         
```

# if
```asciidoc

//int != 0
if(int){} 

//!string.empty()
if(string){}

//false
if(null){} false



```