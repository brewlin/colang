#include "gc.h"
#include "root.h"
#include "Array.h"
#include <stdio.h>
typedef struct obj
{
    int a;
    int b;
    struct obj *next;
}Obj;
Obj *t;
void array_test()
{
    array_t* arr = array_create(8,sizeof(Obj*));

    for (int i = 0; i < 1000; ++i) {
        Obj** tmp = array_push(arr);
        if(i == 168){
            printf("168");
        }
        if(i == 173){
            printf("yes");
        }
        *tmp = gc_malloc(sizeof(Obj));
        (*tmp)->a = i;
        (*tmp)->b = i;
        //printf("p:%p i:%d a:%d b:%d ",*tmp,i,(*tmp)->a,(*tmp)->b);
    }
    Obj** index = arr->addr;
    gc();
    for(int i = 0 ; i < 1000; ++i){
        // printf("i:%d a:%d b:%d \n",i,index[i]->a,index[i]->b);
        if(index[i]->a != i){
            void *st = *(void**)0x111;
        }
        if(index[i]->b != i){
                        void *st = *(void**)0x111;
        }
        assert(index[i]->a == i);
        assert(index[i]->b == i);
    }
    index = NULL;
    arr   = NULL;
    gc();

}
int test_speed()
{
    clock_t start, finish;
    double  duration;
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        int size = rand()%90;
        void* p = gc_malloc(size);
        *(int*)p = size;
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
    return 0;
}

void test_logic(){
    Obj* p1 = gc_malloc(sizeof(Obj));
    p1->a = 10;
    p1->b = 20;
    gc();
    assert(p1->a == 10);
    assert(p1->b == 20);
    p1->next = gc_malloc(sizeof(Obj));
    assert(p1->next);
    p1->next->a = 22;
    p1->next->b = 33;
    gc();
    assert(p1->next->a == 22);
    assert(p1->next->b == 33);
}
void main(){
    sp_start = get_sp();
    array_test();
    gc();
    test_speed();
    test_logic();
    gc();
}
