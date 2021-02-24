#include "gc.h"
#include "root.h"
#include "Hugmem.h"
#include "Token.h"
/**
 * 对该对象进行标记
 * 并进行子对象标记
 * @param ptr
 */
int gc_mark(void * ptr)
{
    if (ptr == NULL)return TRUE;

    poolp pool;
    uint size;
    pool = POOL_ADDR(ptr);
    if((uptr)pool < arenas[0].address || (uptr)pool > (arenas[0].address + ARENA_SIZE)) {
        // mark(&Hugmem,ptr);
        return NOT_STACK;
    }
    if (!Co_ADDRESS_IN_RANGE(ptr, pool)) {
        // mark(&Hugmem,ptr);
        return NOT_STACK;
        // return;
    }

    size = INDEX2SIZE(pool->szidx);

    block *hdr = ptr - 8;
    //这里必须全都是带有header头的
    if(hdr->flags < 1 || hdr->flags > 3){
        return TRUE;
    }
    if (!FL_TEST(hdr->flags, FL_ALLOC)) {
//      printf("flag not set alloc\n");
      return TRUE;
    }
    if (FL_TEST(hdr->flags, FL_MARK)) {
      //printf("flag not set mark\n");
      return TRUE;
    }
    //printf("marking %p:%d ",ptr,*(int*)ptr);
    /* marking */
    FL_SET(hdr->flags, FL_MARK);

    //进行child 节点递归 标记
    for (void* p = ptr; p < (ptr + size -8); p++) {
        //对内存解引用，因为内存里面可能存放了内存的地址 也就是引用，需要进行引用的递归标记
//        gc_mark(*(void **)p);
        if(gc_mark(*(void**)p) == NOT_STACK){
            mark(Hugmem,*(void**)p);
        }
    }
    return TRUE;
}
/**
 * 清除 未标记内存 进行回收利用
 */
void     gc_sweep(void)
{
    //遍历areans_object
    struct arena_object* area = &arenas[0];
    poolp  pool;
    uint   size = 0;

    //从 first_pools - pool_adress 之间遍历
    for (void* p = area->first_address; p < (void*)area->pool_address; p += POOL_SIZE)
    {
        pool = (poolp)p;
        size = INDEX2SIZE(pool->szidx);
        void* start_addr = p + POOL_OVERHEAD;
        void* end_addr = p + POOL_SIZE;
        for (void *pp = start_addr; pp < end_addr; pp += size)
        {
            block *obj = (block*)pp;
            //查看该堆是否已经被使用
            if (FL_TEST(obj->flags, FL_ALLOC)) {
                //查看该堆是否被标记过
                if (FL_TEST(obj->flags, FL_MARK)) {
//                    DEBUG(printf("解除标记 : %p\n", p));
                     //printf("unlock : %p\n", p);
                    FL_UNSET(obj->flags, FL_MARK);
                }else {
//                    DEBUG(printf("clear :%p \n",pp + 8));
                    //printf("clear %p:%p \n",pp,pp + 8);
//                    printf("清除回收 %p:%d ",pp,obj->flags);
                    FL_UNSET(obj->flags, FL_ALLOC);
                    Free(pp);
                }
            }

        }


    }
}
void tell_is_stackarg(void* arg){
    void *top = get_sp();
    if(sp_start > arg && arg > top){
        if(gc_mark(*(void**)arg) == NOT_STACK){
            mark(Hugmem,*(void**)arg);
        }
    }
}
/**
 * 寄存器扫描
 */
void scan_register()
{
//    printf("[gc] start scan register\n");
    void *reg;
    if(reg = get_sp())  tell_is_stackarg(reg);
    if(reg = get_bp())  tell_is_stackarg(reg);
    if(reg = get_di())  tell_is_stackarg(reg);
    if(reg = get_si())  tell_is_stackarg(reg);
    if(reg = get_dx())  tell_is_stackarg(reg);
    if(reg = get_cx())  tell_is_stackarg(reg);
    if(reg = get_r8())  tell_is_stackarg(reg);
    if(reg = get_r9())  tell_is_stackarg(reg);
    if(reg = get_ax())  tell_is_stackarg(reg);
    if(reg = get_bx())  tell_is_stackarg(reg);
}

typedef struct gc_value
{
    long type;
    void* data;
}GCValue;
/**
 * 栈扫描
 */
void scan_stack(){
    //从栈顶开始扫描c栈和co栈
    void * cur_sp = get_sp();
    //高低往低地址增长
    assert(sp_start >= cur_sp);

    //假定我们栈上的都是带有value的指针
    for (; cur_sp < sp_start ; cur_sp += 2){
        void * ptr = *(void**)cur_sp;
        GCValue* v   = (GCValue*)ptr;
        block* hdr  = (block*)(ptr - 8);
        poolp pool;
        uint size;
        pool = POOL_ADDR(ptr);
        if((uptr)pool < arenas[0].address || (uptr)pool > (arenas[0].address + ARENA_SIZE)) {
            continue;
        }
        /**
         * 辨别指针需要做额外的许多操作
         *  1. 判断是否是堆里的数据
         *  2. 判断对象头是否准确(这个栈的数据可能来自语言本身| 也有可能来自c栈)
         *  3. 强制采用类型判断来辨别指针，因为在语言本身的栈只会保留 Value*类型
         */
        if (!Co_ADDRESS_IN_RANGE(ptr, pool)) {
            continue;
        }
        //属于这个pool上 但是又没有header头的有如下情况
        //1. c栈有的地方对string的操作 是被string包装过的
        if(hdr->flags < 1 || hdr->flags > 3){
            stringmark(ptr);
            continue;
        }
        //说明当前内存是一个co栈的 字符串对象 需要单独标记 string->data
        if(v->type == String){
            //TODO: fix 会有 type=string data=1的情况
            stringmark(v->data);
        }
        //这里说明当前内存可能不是由arena分配的，因为超过256byte的数据直接malloc
        //这里调用 hugmem来标记大内存块
        if(gc_mark(ptr) == NOT_STACK){
            mark(Hugmem,ptr);
        }
    }
}
/**
 * 标记清除算法的gc实现
 */
void  gc(void)
{
//     printf("[gc] start gc\n");
    scan_register();
    scan_stack();

    //标记完成后 在进行 清除 对于没有标记过的进行回收
    gc_sweep();
}

