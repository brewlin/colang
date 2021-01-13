#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif
#ifndef WIN32
#define va_list char*
#define va_start(ap,arg) (ap=(va_list)&arg+sizeof(arg))
#define va_arg(ap,t)	(*(t*)((ap+=sizeof(t)) - sizeof(t)))
#define va_end(ap) (ap=(va_list)0)
#else
#include <Windows.h>
#endif


//malloc 
#ifndef NULL
#define NULL (0)
#endif

void free(void* ptr);
void* malloc(unsigned long size);
void* realloc(void *p, unsigned long nbytes);
static long brk(void *end_data_segment);
long mini_crt_init_heap();

//�ַ�
char* itoa(long n,char* str,long radix);
long strcmp(const char* src, const char* dst);
char* strcpy(char* dest, const char* src);
char *strchr (const char *s,int c_in);
void *memcpy(void *dstpp,const void *srcpp, unsigned long int len);
void *memmove (void *__dest, __const void *__src, unsigned long int __n);
int memcmp (__const void *__s1, __const void *__s2, unsigned long int __n);
void *memset (void *dstpp, int c, unsigned long int len);
unsigned long strlen(const char* str);
unsigned int tolower(unsigned int c);
unsigned int toupper(unsigned int c);
char *strcat(char *dest, const char *src);

void assert(int ret);
void __ctype_b_loc();
void __stack_chk_fail();
//�ļ���IO
typedef long FILE;

#define EOF	(-1)

#ifdef WIN32
#define stdin	((FILE*)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout	((FILE*)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr	((FILE*)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin	((FILE*)0)
#define stdout	((FILE*)1)
#define stderr	((FILE*)2)
#endif

//int 0x80中断不能显示64位的地址，所以不能用栈
long write(long fd,const void *buffer,unsigned long size);

long mini_crt_init_io();
FILE* fopen(const char *filename,const char* mode);
long fread(void* buffer,long size,long count,FILE* stream);
long fwrite(const void* buffer,long size,long count,FILE* stream);
long fclose(FILE *fp);
long fseek(FILE* fp,long offset,long set);

//printf
long fputc(char c,FILE* stream);
long putchar(int c);
long puts(const char* str);
long fputs(const char* str,FILE *stream);
long printf(const char *format,...);
long fprintf(FILE* stream,const char *format,...);
long _vsnprintf(char* dstr, const char *format, va_list arglist);
long vsnprintf(char* dstr,const char *format,...);

//internal 
void do_global_ctors();
void mini_crt_call_exit_routine();

//atexit
typedef void(*atexit_func_t )( void );
long atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif


typedef unsigned char byte;

#define BYTE_COPY_FWD(dst_bp, src_bp, nbytes)				      \
  do									      \
    {									      \
      unsigned long int __nbytes = (nbytes);					      \
      while (__nbytes > 0)						      \
	{								      \
	  byte __x = ((byte *) src_bp)[0];				      \
	  src_bp += 1;							      \
	  __nbytes -= 1;						      \
	  ((byte *) dst_bp)[0] = __x;					      \
	  dst_bp += 1;							      \
	}								      \
    } while (0)

#define PAGE_COPY_FWD_MAYBE(dstp, srcp, nbytes_left, nbytes) /* nada */
#define WORD_COPY_FWD(dst_bp, src_bp, nbytes_left, nbytes)		      \
  do									      \
    {									      \
      int __d0;								      \
      asm volatile(/* Clear the direction flag, so copying goes forward.  */  \
		   "cld\n"						      \
		   /* Copy longwords.  */				      \
		   "rep\n"						      \
		   "movsl" :						      \
 		   "=D" (dst_bp), "=S" (src_bp), "=c" (__d0) :		      \
		   "0" (dst_bp), "1" (src_bp), "2" ((nbytes) / 4) :	      \
		   "memory");						      \
      (nbytes_left) = (nbytes) % 4;					      \
    } while (0)
#define BYTE_COPY_FWD(dst_bp, src_bp, nbytes)				      \
  do									      \
    {									      \
      unsigned long int __nbytes = (nbytes);					      \
      while (__nbytes > 0)						      \
	{								      \
	  byte __x = ((byte *) src_bp)[0];				      \
	  src_bp += 1;							      \
	  __nbytes -= 1;						      \
	  ((byte *) dst_bp)[0] = __x;					      \
	  dst_bp += 1;							      \
	}								      \
    } while (0)

# define OP_T_THRES	16
# define op_t	unsigned long int
# define OPSIZ	(sizeof(op_t))

#endif // end __MINI_CRT_H__

