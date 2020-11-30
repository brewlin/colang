#include "gc.h"
#include "root.h"

int main()
{
    sp_start = get_sp();
    clock_t start, finish;
    double  duration;
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        int size = rand()%90;
        void* p = gc_malloc(size);
        *(int*)p = size;
        // printf("%d ",*(int*)p);
//        Free(p);
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
    return 0;
}
