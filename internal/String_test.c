#include "String.h"
#include <stdio.h>
#include "help.h"
#include "limits.h"

#define UNUSED(x) (void)(x)

int test_string(void)
{
    {
        string x = stringnew("foo"), y;

        assert_s("Create a string and obtain the length",
            stringlen(x) == 3 && memcmp(x,"foo\0",4) == 0)

        stringfree(x);
        x = stringnewlen("foo",2);
        assert_s("Create a string with specified length",
            stringlen(x) == 2 && memcmp(x,"fo\0",3) == 0)

        x = stringcat(x,"bar");
        assert_s("Strings concatenation",
            stringlen(x) == 5 && memcmp(x,"fobar\0",6) == 0);

        x = stringcpy(x,"a");
        assert_s("stringcpy() against an originally longer string",
            stringlen(x) == 1 && memcmp(x,"a\0",2) == 0)

        x = stringcpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
        assert_s("stringcpy() against an originally shorter string",
            stringlen(x) == 33 &&
            memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)

        stringfree(x);
        x = stringcatprintf(stringempty(),"%d",123);
        assert_s("stringcatprintf() seems working in the base case",
            stringlen(x) == 3 && memcmp(x,"123\0",4) == 0)

        stringfree(x);
        x = stringnew("--");
        x = stringcatfmt(x, "Hello %s World %I,%I--", "Hi!", LLONG_MIN,LLONG_MAX);
        assert_s("stringcatfmt() seems working in the base case",
            stringlen(x) == 60 &&
            memcmp(x,"--Hello Hi! World -9223372036854775808,"
                     "9223372036854775807--",60) == 0)
        printf("[%s]\n",x);

        stringfree(x);
        x = stringnew("--");
        x = stringcatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
        assert_s("stringcatfmt() seems working with unsigned numbers",
            stringlen(x) == 35 &&
            memcmp(x,"--4294967295,18446744073709551615--",35) == 0)

        stringfree(x);
        x = stringnew(" x ");
        stringtrim(x," x");
        assert_s("stringtrim() works when all chars match",
            stringlen(x) == 0)

        stringfree(x);
        x = stringnew(" x ");
        stringtrim(x," ");
        assert_s("stringtrim() works when a single char remains",
            stringlen(x) == 1 && x[0] == 'x')

        stringfree(x);
        x = stringnew("xxciaoyyy");
        stringtrim(x,"xy");
        assert_s("stringtrim() correctly trims characters",
            stringlen(x) == 4 && memcmp(x,"ciao\0",5) == 0)

        y = stringdup(x);
        stringrange(y,1,1);
        assert_s("stringrange(...,1,1)",
            stringlen(y) == 1 && memcmp(y,"i\0",2) == 0)

        stringfree(y);
        y = stringdup(x);
        stringrange(y,1,-1);
        assert_s("stringrange(...,1,-1)",
            stringlen(y) == 3 && memcmp(y,"iao\0",4) == 0)

        stringfree(y);
        y = stringdup(x);
        stringrange(y,-2,-1);
        assert_s("stringrange(...,-2,-1)",
            stringlen(y) == 2 && memcmp(y,"ao\0",3) == 0)

        stringfree(y);
        y = stringdup(x);
        stringrange(y,2,1);
        assert_s("stringrange(...,2,1)",
            stringlen(y) == 0 && memcmp(y,"\0",1) == 0)

        stringfree(y);
        y = stringdup(x);
        stringrange(y,1,100);
        assert_s("stringrange(...,1,100)",
            stringlen(y) == 3 && memcmp(y,"iao\0",4) == 0)

        stringfree(y);
        y = stringdup(x);
        stringrange(y,100,100);
        assert_s("stringrange(...,100,100)",
            stringlen(y) == 0 && memcmp(y,"\0",1) == 0)

        stringfree(y);
        stringfree(x);
        x = stringnew("foo");
        y = stringnew("foa");
        assert_s("stringcmp(foo,foa)", stringcmp(x,y) > 0)

        stringfree(y);
        stringfree(x);
        x = stringnew("bar");
        y = stringnew("bar");
        assert_s("stringcmp(bar,bar)", stringcmp(x,y) == 0)

        stringfree(y);
        stringfree(x);
        x = stringnew("aar");
        y = stringnew("bar");
        assert_s("stringcmp(bar,bar)", stringcmp(x,y) < 0)

        stringfree(y);
        stringfree(x);
        x = stringnewlen("\a\n\0foo\r",7);
        y = stringcatrepr(stringempty(),x,stringlen(x));
        assert_s("stringcatrepr(...data...)",
            memcmp(y,"\"\\a\\n\\x00foo\\r\"",15) == 0)

        {
            unsigned int oldfree;
            char *p;
            int step = 10, j, i;

            stringfree(x);
            stringfree(y);
            x = stringnew("0");
            assert_s("stringnew() free/len buffers", stringlen(x) == 1 && stringavail(x) == 0);

            /* Run the test a few times in order to hit the first two
             * LSTRING header types. */
            for (i = 0; i < 10; i++) {
                int oldlen = stringlen(x);
                x = stringMakeRoomFor(x,step);
                int type = x[-1]&LSTRING_TYPE_MASK;

                assert_s("stringMakeRoomFor() len", stringlen(x) == oldlen);
                if (type != LSTRING_TYPE_5) {
                    assert_s("stringMakeRoomFor() free", stringavail(x) >= step);
                    oldfree = stringavail(x);
                }
                p = x+oldlen;
                for (j = 0; j < step; j++) {
                    p[j] = 'A'+j;
                }
                stringIncrLen(x,step);
            }
            assert_s("stringMakeRoomFor() content",
                memcmp("0ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ",x,101) == 0);
            assert_s("stringMakeRoomFor() final length",stringlen(x)==101);

            stringfree(x);
        }
    }
    return 0;
}


