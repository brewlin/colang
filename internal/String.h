#ifndef __LSTRING_H
#define __LSTRING_H

#define LSTRING_MAX_PREALLOC (1024*1024)
extern const char *LSTRING_NOINIT;

#include <sys/types.h>
#include <stdarg.h>
#include <stdint.h>

typedef char* string;

/* Note: stringhdr5 is never used, we just access the flags byte directly.
 * However is here to document the layout of type 5 LSTRING strings. */
struct __attribute__ ((__packed__)) stringhdr5 {
    unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
    char buf[];
};
struct __attribute__ ((__packed__)) stringhdr8 {
    uint8_t len; /* used */
    uint8_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) stringhdr16 {
    uint16_t len; /* used */
    uint16_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) stringhdr32 {
    uint32_t len; /* used */
    uint32_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};
struct __attribute__ ((__packed__)) stringhdr64 {
    uint64_t len; /* used */
    uint64_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
    char buf[];
};

#define LSTRING_TYPE_5  0
#define LSTRING_TYPE_8  1
#define LSTRING_TYPE_16 2
#define LSTRING_TYPE_32 3
#define LSTRING_TYPE_64 4
#define LSTRING_TYPE_MASK 7
#define LSTRING_TYPE_BITS 3
#define LSTRING_HDR_VAR(T,s) struct stringhdr##T *sh = (void*)((s)-(sizeof(struct stringhdr##T)));
#define LSTRING_HDR(T,s) ((struct stringhdr##T *)((s)-(sizeof(struct stringhdr##T))))
#define LSTRING_TYPE_5_LEN(f) ((f)>>LSTRING_TYPE_BITS)

static inline size_t stringlen(const string s) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            return LSTRING_TYPE_5_LEN(flags);
        case LSTRING_TYPE_8:
            return LSTRING_HDR(8,s)->len;
        case LSTRING_TYPE_16:
            return LSTRING_HDR(16,s)->len;
        case LSTRING_TYPE_32:
            return LSTRING_HDR(32,s)->len;
        case LSTRING_TYPE_64:
            return LSTRING_HDR(64,s)->len;
    }
    return 0;
}

static inline size_t stringavail(const string s) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5: {
            return 0;
        }
        case LSTRING_TYPE_8: {
            LSTRING_HDR_VAR(8,s);
            return sh->alloc - sh->len;
        }
        case LSTRING_TYPE_16: {
            LSTRING_HDR_VAR(16,s);
            return sh->alloc - sh->len;
        }
        case LSTRING_TYPE_32: {
            LSTRING_HDR_VAR(32,s);
            return sh->alloc - sh->len;
        }
        case LSTRING_TYPE_64: {
            LSTRING_HDR_VAR(64,s);
            return sh->alloc - sh->len;
        }
    }
    return 0;
}

static inline void stringsetlen(string s, size_t newlen) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            {
                unsigned char *fp = ((unsigned char*)s)-1;
                *fp = LSTRING_TYPE_5 | (newlen << LSTRING_TYPE_BITS);
            }
            break;
        case LSTRING_TYPE_8:
            LSTRING_HDR(8,s)->len = newlen;
            break;
        case LSTRING_TYPE_16:
            LSTRING_HDR(16,s)->len = newlen;
            break;
        case LSTRING_TYPE_32:
            LSTRING_HDR(32,s)->len = newlen;
            break;
        case LSTRING_TYPE_64:
            LSTRING_HDR(64,s)->len = newlen;
            break;
    }
}

static inline void stringinclen(string s, size_t inc) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            {
                unsigned char *fp = ((unsigned char*)s)-1;
                unsigned char newlen = LSTRING_TYPE_5_LEN(flags)+inc;
                *fp = LSTRING_TYPE_5 | (newlen << LSTRING_TYPE_BITS);
            }
            break;
        case LSTRING_TYPE_8:
            LSTRING_HDR(8,s)->len += inc;
            break;
        case LSTRING_TYPE_16:
            LSTRING_HDR(16,s)->len += inc;
            break;
        case LSTRING_TYPE_32:
            LSTRING_HDR(32,s)->len += inc;
            break;
        case LSTRING_TYPE_64:
            LSTRING_HDR(64,s)->len += inc;
            break;
    }
}

/* stringalloc() = stringavail() + stringlen() */
static inline size_t stringalloc(const string s) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            return LSTRING_TYPE_5_LEN(flags);
        case LSTRING_TYPE_8:
            return LSTRING_HDR(8,s)->alloc;
        case LSTRING_TYPE_16:
            return LSTRING_HDR(16,s)->alloc;
        case LSTRING_TYPE_32:
            return LSTRING_HDR(32,s)->alloc;
        case LSTRING_TYPE_64:
            return LSTRING_HDR(64,s)->alloc;
    }
    return 0;
}

static inline void stringsetalloc(string s, size_t newlen) {
    unsigned char flags = s[-1];
    switch(flags&LSTRING_TYPE_MASK) {
        case LSTRING_TYPE_5:
            /* Nothing to do, this type has no total allocation info. */
            break;
        case LSTRING_TYPE_8:
            LSTRING_HDR(8,s)->alloc = newlen;
            break;
        case LSTRING_TYPE_16:
            LSTRING_HDR(16,s)->alloc = newlen;
            break;
        case LSTRING_TYPE_32:
            LSTRING_HDR(32,s)->alloc = newlen;
            break;
        case LSTRING_TYPE_64:
            LSTRING_HDR(64,s)->alloc = newlen;
            break;
    }
}
void   stringmark(string s);
string stringnewlen(const void *init, size_t initlen);
string stringnew(const char *init);
string stringempty(void);
string stringdup(const string s);
void stringfree(string s);
string stringgrowzero(string s, size_t len);
string stringcatlen(string s, const void *t, size_t len);
string stringcat(string s, const char *t);
string stringcatstring(string s, const string t);
string stringcpylen(string s, const char *t, size_t len);
string stringcpy(string s, const char *t);

string stringcatvprintf(string s, const char *fmt, va_list ap);
#ifdef __GNUC__
string stringcatprintf(string s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
string stringcatprintf(string s, const char *fmt, ...);
#endif

string stringcatfmt(string s, char const *fmt, ...);
string stringtrim(string s, const char *cset);
void stringrange(string s, ssize_t start, ssize_t end);
void stringupdatelen(string s);
void stringclear(string s);
int stringcmp(const string s1, const string s2);
string *stringsplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count);
void stringfreesplitres(string *tokens, int count);
void stringtolower(string s);
void stringtoupper(string s);
string stringfromlonglong(long long value);
string stringcatrepr(string s, const char *p, size_t len);
string *stringsplitargs(const char *line, int *argc);
string stringmapchars(string s, const char *from, const char *to, size_t setlen);
string stringjoin(char **argv, int argc, char *sep);
string stringjoinstring(string *argv, int argc, const char *sep, size_t seplen);

/* Low level functions exposed to the user API */
string stringMakeRoomFor(string s, size_t addlen);
void stringIncrLen(string s, ssize_t incr);
string stringRemoveFreeSpace(string s);
size_t stringAllocSize(string s);
void *stringAllocPtr(string s);

/* Export the allocator used by LSTRING to the program using LSTRING.
 * Sometimes the program LSTRING is linked to, may use a different set of
 * allocators, but may want to allocate or free things that LSTRING will
 * respectively free or allocate. */
void *string_malloc(size_t size);
void *string_realloc(void *ptr, size_t size);
void string_free(void *ptr);

#ifdef REDIS_TEST
int stringTest(int argc, char *argv[]);
#endif

#endif
