
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include "String.h"
#include "Value.h"

const char *LSTRING_NOINIT = "LSTRING_NOINIT";

static inline int stringHdrSize(char type) {
    switch(type & LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            return sizeof(struct stringhdr5);
        case LSTRING_TYPE_8:
            return sizeof(struct stringhdr8);
        case LSTRING_TYPE_16:
            return sizeof(struct stringhdr16);
        case LSTRING_TYPE_32:
            return sizeof(struct stringhdr32);
        case LSTRING_TYPE_64:
            return sizeof(struct stringhdr64);
    }
    return 0;
}

static inline char stringReqType(size_t string_size) {
    if (string_size < 1<<5)
        return LSTRING_TYPE_5;
    if (string_size < 1<<8)
        return LSTRING_TYPE_8;
    if (string_size < 1<<16)
        return LSTRING_TYPE_16;
#if (LONG_MAX == LLONG_MAX)
    if (string_size < 1ll<<32)
        return LSTRING_TYPE_32;
    return LSTRING_TYPE_64;
#else
    return LSTRING_TYPE_32;
#endif
}

char* value_string_plus(Value* lhs,Value* rhs)
{
    //先判断哪个需要被连接
    Value* dstv = lhs->type == String ? rhs : lhs;
    Value* srcv = lhs->type == String ? lhs : rhs;

    // 在字符串运算中都是从新生成一份内存来进行存储结果
    string tmstr = stringdup(srcv->data);
    switch(dstv->type){
        case Int:
        case Bool:
        case Double:
            tmstr = stringcatfmt(tmstr,"%I",(long)dstv->data);
            return tmstr;
        case String:
            tmstr = stringcat(tmstr,dstv->data);
            return tmstr;
    }
    return tmstr;
}

char* value_string_minus(Value* lhs,Value* rhs)
{
    //字符串的所有相加减直接返回原字符串
    return lhs->type == String ? lhs->data : rhs->data;
}

char* value_string_mul(Value* lhs,Value* rhs)
{
    //如果两个都是字母则返回相加的那部分
    if(lhs->type == String && rhs->type == String){
        string tmstr = stringdup(lhs->data);
        tmstr = stringcat(tmstr,rhs->data);
        return tmstr;
    }

    //说明其中有一个数字 那就多次相加
    long count = lhs->type == Int ? (long)lhs->data : (long)rhs->data;
    Value* srcv = lhs->type == String ? lhs : rhs;

    // 在字符串运算中都是从新生成一份内存来进行存储结果
    string tmstr = stringdup(srcv->data);
    //例如: a = "abc" * 1  需要去除乘以1
    count -= 1;
    for (int i = 0; i < count; ++i) {
        tmstr = stringcat(tmstr,srcv->data);
    }
    return tmstr;
}

int value_string_equal(Value* lhs,Value* rhs){
    //必须为两个string 才能比较
    if(lhs->type != String || rhs->type != String){
        return 0;
    }
    if(stringcmp(lhs->data,rhs->data) == 0){
        return 1;
    }
    return 0;

}
int value_string_notequal(Value* lhs,Value* rhs){
    //必须为两个string 才能比较
    if(lhs->type != String || rhs->type != String){
        return 1;
    }
    //相等就是false  不等就是true
    if(stringcmp(lhs->data,rhs->data) == 0){
        return 0;
    }
    return 1;

}

/* 
 * mystring = stringnewlen("abc",3);
 * //默认会申请一个默认大小的内存
 * mystring = stringnewlen(NULL,0);
 */
string stringnewlen(const void *init, size_t initlen) {
    void *sh;
    string s;
    char type = stringReqType(initlen);
    //空字符串一般被作为 append 使用，类型现在设置为8
    if (type == LSTRING_TYPE_5 && initlen == 0) type = LSTRING_TYPE_8;
    int hdrlen = stringHdrSize(type);
    unsigned char *fp; /* flags pointer. */

    sh = s_malloc(hdrlen+initlen+1);
    if (sh == NULL) return NULL;
    if (init == LSTRING_NOINIT)
        init = NULL;
    else if (!init)
        memset(sh, 0, hdrlen+initlen+1);
    s = (char*)sh+hdrlen;
    fp = ((unsigned char*)s)-1;
    switch(type) {
        case LSTRING_TYPE_5: {
            *fp = type | (initlen << LSTRING_TYPE_BITS);
            break;
        }
        case LSTRING_TYPE_8: {
            LSTRING_HDR_VAR(8,s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case LSTRING_TYPE_16: {
            LSTRING_HDR_VAR(16,s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case LSTRING_TYPE_32: {
            LSTRING_HDR_VAR(32,s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case LSTRING_TYPE_64: {
            LSTRING_HDR_VAR(64,s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
    }
    if (initlen && init)
        memcpy(s, init, initlen);
    s[initlen] = '\0';
    return s;
}

//创建一个0长度的空字符串
string stringempty(void) {
    return stringnewlen("",0);
}

// 初始化一个c风格的字符串
string stringnew(const char *init) {
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return stringnewlen(init, initlen);
}

//复制一个 string
string stringdup(const string s) {
    return stringnewlen(s, stringlen(s));
}

//释放 string，
void stringfree(string s) {
    if (s == NULL) return;
    s_free((char*)s-stringHdrSize(s[-1]));
}

/* Set the string string length to the length as obtained with strlen(), so
 * considering as content only up to the first null term character.
 *
 * This function is useful when the string string is hacked manually in some
 * way, like in the following example:
 *
 * s = stringnew("foobar");
 * s[2] = '\0';
 * stringupdatelen(s);
 * printf("%d\n", stringlen(s));
 *
 * The output will be "2", but if we comment out the call to stringupdatelen()
 * the output will be "6" as the string was modified but the logical length
 * remains 6 bytes. */
void stringupdatelen(string s) {
    size_t reallen = strlen(s);
    stringsetlen(s, reallen);
}

/* Modify an string string in-place to make it empty (zero length).
 * However all the existing buffer is not discarded but set as free space
 * so that next append operations will not require allocations up to the
 * number of bytes previously available. */
void stringclear(string s) {
    stringsetlen(s, 0);
    s[0] = '\0';
}

/* Enlarge the free space at the end of the string string so that the caller
 * is sure that after calling this function can overwrite up to addlen
 * bytes after the end of the string, plus one more byte for nul term.
 *
 * Note: this does not change the *length* of the string string as returned
 * by stringlen(), but only the free buffer space we have. */
string stringMakeRoomFor(string s, size_t addlen) {
    void *sh, *newsh;
    size_t avail = stringavail(s);
    size_t len, newlen;
    char type, oldtype = s[-1] & LSTRING_TYPE_MASK;
    int hdrlen;

    /* Return ASAP if there is enough space left. */
    if (avail >= addlen) return s;

    len = stringlen(s);
    sh = (char*)s-stringHdrSize(oldtype);
    newlen = (len+addlen);
    if (newlen < LSTRING_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += LSTRING_MAX_PREALLOC;

    type = stringReqType(newlen);

    /* Don't use type 5: the user is appending to the string and type 5 is
     * not able to remember empty space, so stringMakeRoomFor() must be called
     * at every appending operation. */
    if (type == LSTRING_TYPE_5) type = LSTRING_TYPE_8;

    hdrlen = stringHdrSize(type);
    if (oldtype==type) {
        newsh = s_realloc(sh, hdrlen+newlen+1);
        if (newsh == NULL) return NULL;
        s = (char*)newsh+hdrlen;
    } else {
        /* Since the header size changes, need to move the string forward,
         * and can't use realloc */
        newsh = s_malloc(hdrlen+newlen+1);
        if (newsh == NULL) return NULL;
        memcpy((char*)newsh+hdrlen, s, len+1);
        s_free(sh);
        s = (char*)newsh+hdrlen;
        s[-1] = type;
        stringsetlen(s, len);
    }
    stringsetalloc(s, newlen);
    return s;
}

/* Reallocate the string string so that it has no free space at the end. The
 * contained string remains not altered, but next concatenation operations
 * will require a reallocation.
 *
 * After the call, the passed string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
string stringRemoveFreeSpace(string s) {
    void *sh, *newsh;
    char type, oldtype = s[-1] & LSTRING_TYPE_MASK;
    int hdrlen, oldhdrlen = stringHdrSize(oldtype);
    size_t len = stringlen(s);
    size_t avail = stringavail(s);
    sh = (char*)s-oldhdrlen;

    /* Return ASAP if there is no space left. */
    if (avail == 0) return s;

    /* Check what would be the minimum LSTRING header that is just good enough to
     * fit this string. */
    type = stringReqType(len);
    hdrlen = stringHdrSize(type);

    /* If the type is the same, or at least a large enough type is still
     * required, we just realloc(), letting the allocator to do the copy
     * only if really needed. Otherwise if the change is huge, we manually
     * reallocate the string to use the different header type. */
    if (oldtype==type || type > LSTRING_TYPE_8) {
        newsh = s_realloc(sh, oldhdrlen+len+1);
        if (newsh == NULL) return NULL;
        s = (char*)newsh+oldhdrlen;
    } else {
        newsh = s_malloc(hdrlen+len+1);
        if (newsh == NULL) return NULL;
        memcpy((char*)newsh+hdrlen, s, len+1);
        s_free(sh);
        s = (char*)newsh+hdrlen;
        s[-1] = type;
        stringsetlen(s, len);
    }
    stringsetalloc(s, len);
    return s;
}

/* Return the total size of the allocation of the specified string string,
 * including:
 * 1) The string header before the pointer.
 * 2) The string.
 * 3) The free buffer at the end if any.
 * 4) The implicit null term.
 */
size_t stringAllocSize(string s) {
    size_t alloc = stringalloc(s);
    return stringHdrSize(s[-1])+alloc+1;
}

/* Return the pointer of the actual LSTRING allocation (normally LSTRING strings
 * are referenced by the start of the string buffer). */
void *stringAllocPtr(string s) {
    return (void*) (s-stringHdrSize(s[-1]));
}

/* Increment the string length and decrements the left free space at the
 * end of the string according to 'incr'. Also set the null term
 * in the new end of the string.
 *
 * This function is used in order to fix the string length after the
 * user calls stringMakeRoomFor(), writes something after the end of
 * the current string, and finally needs to set the new length.
 *
 * Note: it is possible to use a negative increment in order to
 * right-trim the string.
 *
 * Usage example:
 *
 * Using stringIncrLen() and stringMakeRoomFor() it is possible to mount the
 * following schema, to cat bytes coming from the kernel to the end of an
 * string string without copying into an intermediate buffer:
 *
 * oldlen = stringlen(s);
 * s = stringMakeRoomFor(s, BUFFER_SIZE);
 * nread = read(fd, s+oldlen, BUFFER_SIZE);
 * ... check for nread <= 0 and handle it ...
 * stringIncrLen(s, nread);
 */
void stringIncrLen(string s, ssize_t incr) {
    unsigned char flags = s[-1];
    size_t len;
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5: {
            unsigned char *fp = ((unsigned char*)s)-1;
            unsigned char oldlen = LSTRING_TYPE_5_LEN(flags);
            assert((incr > 0 && oldlen+incr < 32) || (incr < 0 && oldlen >= (unsigned int)(-incr)));
            *fp = LSTRING_TYPE_5 | ((oldlen+incr) << LSTRING_TYPE_BITS);
            len = oldlen+incr;
            break;
        }
        case LSTRING_TYPE_8: {
            LSTRING_HDR_VAR(8,s);
            assert((incr >= 0 && sh->alloc-sh->len >= incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
            len = (sh->len += incr);
            break;
        }
        case LSTRING_TYPE_16: {
            LSTRING_HDR_VAR(16,s);
            assert((incr >= 0 && sh->alloc-sh->len >= incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
            len = (sh->len += incr);
            break;
        }
        case LSTRING_TYPE_32: {
            LSTRING_HDR_VAR(32,s);
            assert((incr >= 0 && sh->alloc-sh->len >= (unsigned int)incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
            len = (sh->len += incr);
            break;
        }
        case LSTRING_TYPE_64: {
            LSTRING_HDR_VAR(64,s);
            assert((incr >= 0 && sh->alloc-sh->len >= (uint64_t)incr) || (incr < 0 && sh->len >= (uint64_t)(-incr)));
            len = (sh->len += incr);
            break;
        }
        default: len = 0; /* Just to avoid compilation warnings. */
    }
    s[len] = '\0';
}

/* Grow the string to have the specified length. Bytes that were not part of
 * the original length of the string will be set to zero.
 *
 * if the specified length is smaller than the current length, no operation
 * is performed. */
string stringgrowzero(string s, size_t len) {
    size_t curlen = stringlen(s);

    if (len <= curlen) return s;
    s = stringMakeRoomFor(s,len-curlen);
    if (s == NULL) return NULL;

    /* Make sure added region doesn't contain garbage */
    memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
    stringsetlen(s, len);
    return s;
}

/* Append the specified binary-safe string pointed by 't' of 'len' bytes to the
 * end of the specified string string 's'.
 *
 * After the call, the passed string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
string stringcatlen(string s, const void *t, size_t len) {
    size_t curlen = stringlen(s);

    s = stringMakeRoomFor(s,len);
    if (s == NULL) return NULL;
    memcpy(s+curlen, t, len);
    stringsetlen(s, curlen+len);
    s[curlen+len] = '\0';
    return s;
}

/* Append the specified null terminated C string to the string string 's'.
 *
 * After the call, the passed string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
string stringcat(string s, const char *t) {
    return stringcatlen(s, t, strlen(t));
}

/* Append the specified string 't' to the existing string 's'.
 *
 * After the call, the modified string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
string stringcatstring(string s, const string t) {
    return stringcatlen(s, t, stringlen(t));
}

/* Destructively modify the string string 's' to hold the specified binary
 * safe string pointed by 't' of length 'len' bytes. */
string stringcpylen(string s, const char *t, size_t len) {
    if (stringalloc(s) < len) {
        s = stringMakeRoomFor(s,len-stringlen(s));
        if (s == NULL) return NULL;
    }
    memcpy(s, t, len);
    s[len] = '\0';
    stringsetlen(s, len);
    return s;
}

/* Like stringcpylen() but 't' must be a null-termined string so that the length
 * of the string is obtained with strlen(). */
string stringcpy(string s, const char *t) {
    return stringcpylen(s, t, strlen(t));
}

/* Helper for stringcatlonglong() doing the actual number -> string
 * conversion. 's' must point to a string with room for at least
 * LSTRING_LLSTR_SIZE bytes.
 *
 * The function returns the length of the null-terminated string
 * representation stored at 's'. */
#define LSTRING_LLSTR_SIZE 21
int stringll2str(char *s, long long value) {
    char *p, aux;
    unsigned long long v;
    size_t l;

    /* Generate the string representation, this method produces
     * a reversed string. */
    v = (value < 0) ? -value : value;
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);
    if (value < 0) *p++ = '-';

    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/* Identical stringll2str(), but for unsigned long long type. */
int stringull2str(char *s, unsigned long long v) {
    char *p, aux;
    size_t l;

    /* Generate the string representation, this method produces
     * a reversed string. */
    p = s;
    do {
        *p++ = '0'+(v%10);
        v /= 10;
    } while(v);

    /* Compute length and add null term. */
    l = p-s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while(s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/* Create an string string from a long long value. It is much faster than:
 *
 * stringcatprintf(stringempty(),"%lld\n", value);
 */
string stringfromlonglong(long long value) {
    char buf[LSTRING_LLSTR_SIZE];
    int len = stringll2str(buf,value);

    return stringnewlen(buf,len);
}

/* Like stringcatprintf() but gets va_list instead of being variadic. */
string stringcatvprintf(string s, const char *fmt, va_list ap) {
    va_list cpy;
    char staticbuf[1024], *buf = staticbuf, *t;
    size_t buflen = strlen(fmt)*2;

    /* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
    if (buflen > sizeof(staticbuf)) {
        buf = s_malloc(buflen);
        if (buf == NULL) return NULL;
    } else {
        buflen = sizeof(staticbuf);
    }

    /* Try with buffers two times bigger every time we fail to
     * fit the string in the current buffer size. */
    while(1) {
        buf[buflen-2] = '\0';
        va_copy(cpy,ap);
        vsnprintf(buf, buflen, fmt, cpy);
        va_end(cpy);
        if (buf[buflen-2] != '\0') {
            if (buf != staticbuf) s_free(buf);
            buflen *= 2;
            buf = s_malloc(buflen);
            if (buf == NULL) return NULL;
            continue;
        }
        break;
    }

    /* Finally concat the obtained string to the LSTRING string and return it. */
    t = stringcat(s, buf);
    if (buf != staticbuf) s_free(buf);
    return t;
}

/* Append to the string string 's' a string obtained using printf-alike format
 * specifier.
 *
 * After the call, the modified string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = stringnew("Sum is: ");
 * s = stringcatprintf(s,"%d+%d = %d",a,b,a+b).
 *
 * Often you need to create a string from scratch with the printf-alike
 * format. When this is the need, just use stringempty() as the target string:
 *
 * s = stringcatprintf(stringempty(), "... your format ...", args);
 */
string stringcatprintf(string s, const char *fmt, ...) {
    va_list ap;
    char *t;
    va_start(ap, fmt);
    t = stringcatvprintf(s,fmt,ap);
    va_end(ap);
    return t;
}

/* This function is similar to stringcatprintf, but much faster as it does
 * not rely on sprintf() family functions implemented by the libc that
 * are often very slow. Moreover directly handling the string string as
 * new data is concatenated provides a performance improvement.
 *
 * However this function only handles an incompatible subset of printf-alike
 * format specifiers:
 *
 * %s - C String
 * %S - LSTRING string
 * %i - signed int
 * %I - 64 bit signed integer (long long, int64_t)
 * %u - unsigned int
 * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
 * %% - Verbatim "%" character.
 */
string stringcatfmt(string s, char const *fmt, ...) {
    size_t initlen = stringlen(s);
    const char *f = fmt;
    long i;
    va_list ap;

    /* To avoid continuous reallocations, let's start with a buffer that
     * can hold at least two times the format string itself. It's not the
     * best heuristic but seems to work in practice. */
    s = stringMakeRoomFor(s, initlen + strlen(fmt)*2);
    va_start(ap,fmt);
    f = fmt;    /* Next format specifier byte to process. */
    i = initlen; /* Position of the next byte to write to dest str. */
    while(*f) {
        char next, *str;
        size_t l;
        long long num;
        unsigned long long unum;

        /* Make sure there is always space for at least 1 char. */
        if (stringavail(s)==0) {
            s = stringMakeRoomFor(s,1);
        }

        switch(*f) {
        case '%':
            next = *(f+1);
            f++;
            switch(next) {
            case 's':
            case 'S':
                str = va_arg(ap,char*);
                l = (next == 's') ? strlen(str) : stringlen(str);
                if (stringavail(s) < l) {
                    s = stringMakeRoomFor(s,l);
                }
                memcpy(s+i,str,l);
                stringinclen(s,l);
                i += l;
                break;
            case 'i':
            case 'I':
                if (next == 'i')
                    num = va_arg(ap,int);
                else
                    num = va_arg(ap,long long);
                {
                    char buf[LSTRING_LLSTR_SIZE];
                    l = stringll2str(buf,num);
                    if (stringavail(s) < l) {
                        s = stringMakeRoomFor(s,l);
                    }
                    memcpy(s+i,buf,l);
                    stringinclen(s,l);
                    i += l;
                }
                break;
            case 'u':
            case 'U':
                if (next == 'u')
                    unum = va_arg(ap,unsigned int);
                else
                    unum = va_arg(ap,unsigned long long);
                {
                    char buf[LSTRING_LLSTR_SIZE];
                    l = stringull2str(buf,unum);
                    if (stringavail(s) < l) {
                        s = stringMakeRoomFor(s,l);
                    }
                    memcpy(s+i,buf,l);
                    stringinclen(s,l);
                    i += l;
                }
                break;
            default: /* Handle %% and generally %<unknown>. */
                s[i++] = next;
                stringinclen(s,1);
                break;
            }
            break;
        default:
            s[i++] = *f;
            stringinclen(s,1);
            break;
        }
        f++;
    }
    va_end(ap);

    /* Add null-term */
    s[i] = '\0';
    return s;
}

/* Remove the part of the string from left and from right composed just of
 * contiguous characters found in 'cset', that is a null terminted C string.
 *
 * After the call, the modified string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = stringnew("AA...AA.a.aa.aHelloWorld     :::");
 * s = stringtrim(s,"Aa. :");
 * printf("%s\n", s);
 *
 * Output will be just "HelloWorld".
 */
string stringtrim(string s, const char *cset) {
    char *start, *end, *sp, *ep;
    size_t len;

    sp = start = s;
    ep = end = s+stringlen(s)-1;
    while(sp <= end && strchr(cset, *sp)) sp++;
    while(ep > sp && strchr(cset, *ep)) ep--;
    len = (sp > ep) ? 0 : ((ep-sp)+1);
    if (s != sp) memmove(s, sp, len);
    s[len] = '\0';
    stringsetlen(s,len);
    return s;
}

/* Turn the string into a smaller (or equal) string containing only the
 * substring specified by the 'start' and 'end' indexes.
 *
 * start and end can be negative, where -1 means the last character of the
 * string, -2 the penultimate character, and so forth.
 *
 * The interval is inclusive, so the start and end characters will be part
 * of the resulting string.
 *
 * The string is modified in-place.
 *
 * Example:
 *
 * s = stringnew("Hello World");
 * stringrange(s,1,-1); => "ello World"
 */
void stringrange(string s, ssize_t start, ssize_t end) {
    size_t newlen, len = stringlen(s);

    if (len == 0) return;
    if (start < 0) {
        start = len+start;
        if (start < 0) start = 0;
    }
    if (end < 0) {
        end = len+end;
        if (end < 0) end = 0;
    }
    newlen = (start > end) ? 0 : (end-start)+1;
    if (newlen != 0) {
        if (start >= (ssize_t)len) {
            newlen = 0;
        } else if (end >= (ssize_t)len) {
            end = len-1;
            newlen = (start > end) ? 0 : (end-start)+1;
        }
    } else {
        start = 0;
    }
    if (start && newlen) memmove(s, s+start, newlen);
    s[newlen] = 0;
    stringsetlen(s,newlen);
}

/* Apply tolower() to every character of the string string 's'. */
void stringtolower(string s) {
    size_t len = stringlen(s), j;

    for (j = 0; j < len; j++) s[j] = tolower(s[j]);
}

/* Apply toupper() to every character of the string string 's'. */
void stringtoupper(string s) {
    size_t len = stringlen(s), j;

    for (j = 0; j < len; j++) s[j] = toupper(s[j]);
}

/* Compare two string strings s1 and s2 with memcmp().
 *
 * Return value:
 *
 *     positive if s1 > s2.
 *     negative if s1 < s2.
 *     0 if s1 and s2 are exactly the same binary string.
 *
 * If two strings share exactly the same prefix, but one of the two has
 * additional characters, the longer string is considered to be greater than
 * the smaller one. */
int stringcmp(const string s1, const string s2) {
    size_t l1, l2, minlen;
    int cmp;

    l1 = stringlen(s1);
    l2 = stringlen(s2);
    minlen = (l1 < l2) ? l1 : l2;
    cmp = memcmp(s1,s2,minlen);
    if (cmp == 0) return l1>l2? 1: (l1<l2? -1: 0);
    return cmp;
}

/* Split 's' with separator in 'sep'. An array
 * of string strings is returned. *count will be set
 * by reference to the number of tokens returned.
 *
 * On out of memory, zero length string, zero length
 * separator, NULL is returned.
 *
 * Note that 'sep' is able to split a string using
 * a multi-character separator. For example
 * stringsplit("foo_-_bar","_-_"); will return two
 * elements "foo" and "bar".
 *
 * This version of the function is binary-safe but
 * requires length arguments. stringsplit() is just the
 * same function but for zero-terminated strings.
 */
string *stringsplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count) {
    int elements = 0, slots = 5;
    long start = 0, j;
    string *tokens;

    if (seplen < 1 || len < 0) return NULL;

    tokens = s_malloc(sizeof(string)*slots);
    if (tokens == NULL) return NULL;

    if (len == 0) {
        *count = 0;
        return tokens;
    }
    for (j = 0; j < (len-(seplen-1)); j++) {
        /* make sure there is room for the next element and the final one */
        if (slots < elements+2) {
            string *newtokens;

            slots *= 2;
            newtokens = s_realloc(tokens,sizeof(string)*slots);
            if (newtokens == NULL) goto cleanup;
            tokens = newtokens;
        }
        /* search the separator */
        if ((seplen == 1 && *(s+j) == sep[0]) || (memcmp(s+j,sep,seplen) == 0)) {
            tokens[elements] = stringnewlen(s+start,j-start);
            if (tokens[elements] == NULL) goto cleanup;
            elements++;
            start = j+seplen;
            j = j+seplen-1; /* skip the separator */
        }
    }
    /* Add the final element. We are sure there is room in the tokens array. */
    tokens[elements] = stringnewlen(s+start,len-start);
    if (tokens[elements] == NULL) goto cleanup;
    elements++;
    *count = elements;
    return tokens;

cleanup:
    {
        int i;
        for (i = 0; i < elements; i++) stringfree(tokens[i]);
        s_free(tokens);
        *count = 0;
        return NULL;
    }
}

/* Free the result returned by stringsplitlen(), or do nothing if 'tokens' is NULL. */
void stringfreesplitres(string *tokens, int count) {
    if (!tokens) return;
    while(count--)
        stringfree(tokens[count]);
    s_free(tokens);
}

/* Append to the string string "s" an escaped string representation where
 * all the non-printable characters (tested with isprint()) are turned into
 * escapes in the form "\n\r\a...." or "\x<hex-number>".
 *
 * After the call, the modified string string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
string stringcatrepr(string s, const char *p, size_t len) {
    s = stringcatlen(s,"\"",1);
    while(len--) {
        switch(*p) {
        case '\\':
        case '"':
            s = stringcatprintf(s,"\\%c",*p);
            break;
        case '\n': s = stringcatlen(s,"\\n",2); break;
        case '\r': s = stringcatlen(s,"\\r",2); break;
        case '\t': s = stringcatlen(s,"\\t",2); break;
        case '\a': s = stringcatlen(s,"\\a",2); break;
        case '\b': s = stringcatlen(s,"\\b",2); break;
        default:
            if (isprint(*p))
                s = stringcatprintf(s,"%c",*p);
            else
                s = stringcatprintf(s,"\\x%02x",(unsigned char)*p);
            break;
        }
        p++;
    }
    return stringcatlen(s,"\"",1);
}

/* Helper function for stringsplitargs() that returns non zero if 'c'
 * is a valid hex digit. */
int is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

/* Helper function for stringsplitargs() that converts a hex digit into an
 * integer from 0 to 15 */
int hex_digit_to_int(char c) {
    switch(c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    default: return 0;
    }
}

/* Split a line into arguments, where every argument can be in the
 * following programming-language REPL-alike form:
 *
 * foo bar "newline are supported\n" and "\xff\x00otherstuff"
 *
 * The number of arguments is stored into *argc, and an array
 * of string is returned.
 *
 * The caller should free the resulting array of string strings with
 * stringfreesplitres().
 *
 * Note that stringcatrepr() is able to convert back a string into
 * a quoted string in the same format stringsplitargs() is able to parse.
 *
 * The function returns the allocated tokens on success, even when the
 * input string is empty, or NULL if the input contains unbalanced
 * quotes or closed quotes followed by non space characters
 * as in: "foo"bar or "foo'
 */
string *stringsplitargs(const char *line, int *argc) {
    const char *p = line;
    char *current = NULL;
    char **vector = NULL;

    *argc = 0;
    while(1) {
        /* skip blanks */
        while(*p && isspace(*p)) p++;
        if (*p) {
            /* get a token */
            int inq=0;  /* set to 1 if we are in "quotes" */
            int insq=0; /* set to 1 if we are in 'single quotes' */
            int done=0;

            if (current == NULL) current = stringempty();
            while(!done) {
                if (inq) {
                    if (*p == '\\' && *(p+1) == 'x' &&
                                             is_hex_digit(*(p+2)) &&
                                             is_hex_digit(*(p+3)))
                    {
                        unsigned char byte;

                        byte = (hex_digit_to_int(*(p+2))*16)+
                                hex_digit_to_int(*(p+3));
                        current = stringcatlen(current,(char*)&byte,1);
                        p += 3;
                    } else if (*p == '\\' && *(p+1)) {
                        char c;

                        p++;
                        switch(*p) {
                        case 'n': c = '\n'; break;
                        case 'r': c = '\r'; break;
                        case 't': c = '\t'; break;
                        case 'b': c = '\b'; break;
                        case 'a': c = '\a'; break;
                        default: c = *p; break;
                        }
                        current = stringcatlen(current,&c,1);
                    } else if (*p == '"') {
                        /* closing quote must be followed by a space or
                         * nothing at all. */
                        if (*(p+1) && !isspace(*(p+1))) goto err;
                        done=1;
                    } else if (!*p) {
                        /* unterminated quotes */
                        goto err;
                    } else {
                        current = stringcatlen(current,p,1);
                    }
                } else if (insq) {
                    if (*p == '\\' && *(p+1) == '\'') {
                        p++;
                        current = stringcatlen(current,"'",1);
                    } else if (*p == '\'') {
                        /* closing quote must be followed by a space or
                         * nothing at all. */
                        if (*(p+1) && !isspace(*(p+1))) goto err;
                        done=1;
                    } else if (!*p) {
                        /* unterminated quotes */
                        goto err;
                    } else {
                        current = stringcatlen(current,p,1);
                    }
                } else {
                    switch(*p) {
                    case ' ':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\0':
                        done=1;
                        break;
                    case '"':
                        inq=1;
                        break;
                    case '\'':
                        insq=1;
                        break;
                    default:
                        current = stringcatlen(current,p,1);
                        break;
                    }
                }
                if (*p) p++;
            }
            /* add the token to the vector */
            vector = s_realloc(vector,((*argc)+1)*sizeof(char*));
            vector[*argc] = current;
            (*argc)++;
            current = NULL;
        } else {
            /* Even on empty input string return something not NULL. */
            if (vector == NULL) vector = s_malloc(sizeof(void*));
            return vector;
        }
    }

err:
    while((*argc)--)
        stringfree(vector[*argc]);
    s_free(vector);
    if (current) stringfree(current);
    *argc = 0;
    return NULL;
}

/* Modify the string substituting all the occurrences of the set of
 * characters specified in the 'from' string to the corresponding character
 * in the 'to' array.
 *
 * For instance: stringmapchars(mystring, "ho", "01", 2)
 * will have the effect of turning the string "hello" into "0ell1".
 *
 * The function returns the string string pointer, that is always the same
 * as the input pointer since no resize is needed. */
string stringmapchars(string s, const char *from, const char *to, size_t setlen) {
    size_t j, i, l = stringlen(s);

    for (j = 0; j < l; j++) {
        for (i = 0; i < setlen; i++) {
            if (s[j] == from[i]) {
                s[j] = to[i];
                break;
            }
        }
    }
    return s;
}

/* Join an array of C strings using the specified separator (also a C string).
 * Returns the result as an string string. */
string stringjoin(char **argv, int argc, char *sep) {
    string join = stringempty();
    int j;

    for (j = 0; j < argc; j++) {
        join = stringcat(join, argv[j]);
        if (j != argc-1) join = stringcat(join,sep);
    }
    return join;
}

/* Like stringjoin, but joins an array of LSTRING strings. */
string stringjoinstring(string *argv, int argc, const char *sep, size_t seplen) {
    string join = stringempty();
    int j;

    for (j = 0; j < argc; j++) {
        join = stringcatstring(join, argv[j]);
        if (j != argc-1) join = stringcatlen(join,sep,seplen);
    }
    return join;
}

/* Wrappers to the allocators used by LSTRING. Note that LSTRING will actually
 * just use the macros defined into stringalloc.h in order to avoid to pay
 * the overhead of function calls. Here we define these wrappers only for
 * the programs LSTRING is linked to, if they want to touch the LSTRING internals
 * even if they use a different allocator. */
void *string_malloc(size_t size) { return s_malloc(size); }
void *string_realloc(void *ptr, size_t size) { return s_realloc(ptr,size); }
void string_free(void *ptr) { s_free(ptr); }

