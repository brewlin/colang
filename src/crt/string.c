#include "minicrt.h"
char* itoa(long n,char* str,long radix)
{
	char digit[]	="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* p	= str;
	char* head = str;
	if (!p || radix < 2 || radix > 36)
	{
		return p;
	}

	if (radix != 10 && n < 0)
	{
		return p;
	}

	if (n == 0)
	{
		*p++	= '0';
		*p		= 0;
		return p;
	}

	if (radix == 10 && n < 0)
	{
		*p++	= '-';
		n		= -n;
	}

	while (n)
	{
		*p++	= digit[n%radix];
		n	/= radix;
	}

	*p		= 0;
	for (--p; head < p; ++head,--p)
	{
		char temp	= *head;
		*head		= *p;
		*p			= temp;
	}

	return str;
}

long strcmp(const char* src, const char* dst)
{
	long ret	= 0;
	unsigned char* p1	= (unsigned char*)src;
	unsigned char* p2	= (unsigned char*)dst;

	while(!(ret = *p1 - *p2)&&*p2)
		++p1,++p2;
	if (ret < 0)
	{
		ret	= -1;
	}
	else if (ret > 0)
	{
		ret	= 1;
	}

	return (ret);
}
/**
 *
 * @param s
 * @param c_in
 * @return
 */
char *strchr (const char *s,int c_in)
{
	const unsigned char *char_ptr;
	const unsigned long int *longword_ptr;
	unsigned long int longword, magic_bits, charmask;
	unsigned char c;

	c = (unsigned char) c_in;

	/* Handle the first few characters by reading one character at a time.
	   Do this until CHAR_PTR is aligned on a longword boundary.  */
	for (char_ptr = (const unsigned char *) s;
		((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0;
	++char_ptr)
	if (*char_ptr == c)
	return (void *) char_ptr;
	else if (*char_ptr == '\0')
	return NULL;

	longword_ptr = (unsigned long int *) char_ptr;

	switch (sizeof (longword))
	{
		case 4: magic_bits = 0x7efefeffL; break;
		case 8: magic_bits = ((0x7efefefeL << 16) << 16) | 0xfefefeffL; break;
		default:
		abort ();
	}

	/* Set up a longword, each of whose bytes is C.  */
	charmask = c | (c << 8);
	charmask |= charmask << 16;
	if (sizeof (longword) > 4)
	/* Do the shift in two steps to avoid a warning if long has 32 bits.  */
	charmask |= (charmask << 16) << 16;
	if (sizeof (longword) > 8)
	abort ();

	for (;;)
	{


	longword = *longword_ptr++;

	/* Add MAGIC_BITS to LONGWORD.  */
	if ((((longword + magic_bits)

	/* Set those bits that were unchanged by the addition.  */
	^ ~longword)

	/* Look at only the hole bits.  If any of the hole bits
	   are unchanged, most likely one of the bytes was a
	   zero.  */
	& ~magic_bits) != 0 ||

	/* That caught zeroes.  Now test for C.  */
	((((longword ^ charmask) + magic_bits) ^ ~(longword ^ charmask))
	& ~magic_bits) != 0)
	{
	/* Which of the bytes was C or zero?
	   If none of them were, it was a misfire; continue the search.  */

	const unsigned char *cp = (const unsigned char *) (longword_ptr - 1);

	if (*cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (*++cp == c)
		return (char *) cp;
	else if (*cp == '\0')
		return NULL;
	if (sizeof (longword) > 4)
	{
		if (*++cp == c)
			return (char *) cp;
		else if (*cp == '\0')
			return NULL;
		if (*++cp == c)
			return (char *) cp;
		else if (*cp == '\0')
			return NULL;
		if (*++cp == c)
			return (char *) cp;
		else if (*cp == '\0')
			return NULL;
		if (*++cp == c)
			return (char *) cp;
		else if (*cp == '\0')
		return NULL;
	}
	}
	}

	return NULL;
}
char * strcpy(char* dest, const char* src)
{
	char* ret	= dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest	= '\0';
	return ret;

}
/**
 *
 * @param dstpp
 * @param srcpp
 * @param len
 * @return
 */
void *memcpy(void *dstpp,const void *srcpp, unsigned long int len)
{
	unsigned long int dstp = (long int) dstpp;
	unsigned long int srcp = (long int) srcpp;

	/* Copy from the beginning to the end.  */

	/* If there not too few bytes to copy, use word copy.  */
	if (len >= OP_T_THRES)
	{
		/* Copy just a few bytes to make DSTP aligned.  */
		len -= (-dstp) % OPSIZ;
		BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

		/* Copy whole pages from SRCP to DSTP by virtual address manipulation,
       as much as possible.  */

		PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);

		/* Copy from SRCP to DSTP taking advantage of the known alignment of
       DSTP.  Number of bytes remaining is put in the third argument,
       i.e. in LEN.  This number may vary from machine to machine.  */

		WORD_COPY_FWD (dstp, srcp, len, len);

		/* Fall out and copy the tail.  */
	}

	/* There are just a few bytes to copy.  Use byte memory operations.  */
	BYTE_COPY_FWD (dstp, srcp, len);

	return dstpp;
}
void *memmove (void *__dest, __const void *__src, unsigned long int __n)
{
	register unsigned long int __d0, __d1, __d2;
	register void *__tmp = __dest;
	if (__dest < __src)
		__asm__ __volatile__
		("cld\n\t"
		 "rep; movsb"
		: "=&c" (__d0), "=&S" (__d1), "=&D" (__d2),
		"=m" ( *(struct { __extension__ char __x[__n]; } *)__dest)
		: "0" (__n), "1" (__src), "2" (__tmp),
		"m" ( *(struct { __extension__ char __x[__n]; } *)__src));
	else
		__asm__ __volatile__
		("std\n\t"
		 "rep; movsb\n\t"
		 "cld"
		: "=&c" (__d0), "=&S" (__d1), "=&D" (__d2),
		"=m" ( *(struct { __extension__ char __x[__n]; } *)__dest)
		: "0" (__n), "1" (__n - 1 + (__const char *) __src),
		"2" (__n - 1 + (char *) __tmp),
		"m" ( *(struct { __extension__ char __x[__n]; } *)__src));
	return __dest;
}
int memcmp (__const void *__s1, __const void *__s2, unsigned long int __n)
{
	register unsigned long int __d0, __d1, __d2;
	register int __res;
	__asm__ __volatile__
	("cld\n\t"
	 "test %3,%3\n\t"
	 "repe; cmpsb\n\t"
	 "je	1f\n\t"
	 "sbb	%0,%0\n\t"
	 "or	$1,%0\n"
	 "1:"
	: "=&a" (__res), "=&S" (__d0), "=&D" (__d1), "=&c" (__d2)
	: "0" (0), "1" (__s1), "2" (__s2), "3" (__n),
	"m" ( *(struct { __extension__ char __x[__n]; } *)__s1),
	"m" ( *(struct { __extension__ char __x[__n]; } *)__s2)
	: "cc");
	return __res;
}
unsigned long strlen(const char* str)
{
	long cnt	= 0;
	if(!str)
		return 0;
	for (;*str != '\0';++str)
	{
		++cnt;
	}

	return cnt;
}
void *memset (void *dstpp, int c, unsigned long int len)
{
	int d0;
	unsigned long int dstp = (unsigned long int) dstpp;

	/* This explicit register allocation
       improves code very much indeed.  */
	register op_t x asm("ax");

	x = (unsigned char) c;

	/* Clear the direction flag, so filling will move forward.  */
	asm volatile("cld");

	/* This threshold value is optimal.  */
	if (len >= 12)
	{
		/* Fill X with four copies of the char we want to fill with.  */
		x |= (x << 8);
		x |= (x << 16);

		/* Adjust LEN for the bytes handled in the first loop.  */
		len -= (-dstp) % OPSIZ;

		/* There are at least some bytes to set.
       No need to test for LEN == 0 in this alignment loop.  */

		/* Fill bytes until DSTP is aligned on a longword boundary.  */
		asm volatile("rep\n"
					 "stosb" /* %0, %2, %3 */ :
		"=D" (dstp), "=c" (d0) :
		"0" (dstp), "1" ((-dstp) % OPSIZ), "a" (x) :
		"memory");

		/* Fill longwords.  */
		asm volatile("rep\n"
					 "stosl" /* %0, %2, %3 */ :
		"=D" (dstp), "=c" (d0) :
		"0" (dstp), "1" (len / OPSIZ), "a" (x) :
		"memory");
		len %= OPSIZ;
	}

	/* Write the last few bytes.  */
	asm volatile("rep\n"
				 "stosb" /* %0, %2, %3 */ :
	"=D" (dstp), "=c" (d0) :
	"0" (dstp), "1" (len), "a" (x) :
	"memory");

	return dstpp;
}
// 自定义的tolower函数。
unsigned int tolower(unsigned int c)
{
	if (c>='A' && c<='Z') return c+32;
	else return c;
}

unsigned int toupper(unsigned int c)
{
	if (c>='a' && c<='z') return c-32;
	else return c;
}

/**
 *
 * @param dest
 * @param src
 * @return
 */
char *strcat(char *dest, const char *src)
{
	char *s1 = dest;
	const char *s2 = src;
	char c;

	/* Find the end of the string.  */
	do
		c = *s1++;
	while (c != '\0');

	/* Make S1 point before the next character, so we can increment
       it while memory is read (wins on pipelined cpus).  */
	s1 -= 2;

	do
	{
		c = *s2++;
		*++s1 = c;
	}
	while (c != '\0');

	return dest;
}
