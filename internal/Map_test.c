#include "String.h"
#include <stdio.h>
#include "help.h"
#include "limits.h"
#include "Array.h"
#include "Map.h"
#include "Value.h"
#include "gcmalloc.h"

void test_map()
{
    Value *tree     = map_create();
    assert_s("map_init() test",tree != NULL);

    Value* vars[10];
    Value* v;
    for (int i = 0; i < 10; ++i) {
        if (i < 5)
        {
            vars[i] = newobject(Int, i);
            map_insert(tree,vars[i]);
            v = map_find(tree,vars[i]);
            assert_s("map_insert() int",v->data == vars[i]->data);
        } else {
            const char *str = "test";
            string s = stringnew(str);
            s = stringcatfmt(s, "%I", i);
            vars[i] = newobject(String, s);
            map_insert(tree,vars[i]);
            v = map_find(tree,vars[i]);
            assert_s("map_insert() string",stringcmp(v->data,vars[i]->data) == 0);
        }
    }

}


