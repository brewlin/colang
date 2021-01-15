#include "minicrt.h"

char __fputc_tmp_val__ = 0;
long fputc(char c,FILE* stream)
{

	__fputc_tmp_val__ = c;
	if (fwrite(&__fputc_tmp_val__,1,1,stream) != 1)
	{
		return EOF;
	} 
	else
	{
		return c;
	}
}
long putchar(int c){
    fputc(c,stdout);
}
long puts(const char* str){
	fputs(str,stdout);
}

char __fputs_tmp_array__[256] = {0};
int __fputs_tmp_size__ = 256;
long fputs(const char* str,FILE *stream)
{
//	char __fputs_tmp_array__[256] = {0};
//	int __fputs_tmp_size__ = 256;
	long len		= strlen(str);
	if( len >= __fputs_tmp_size__ )
		return EOF;
	strcpy( __fputs_tmp_array__,str );
	if (fwrite(__fputs_tmp_array__,1,len,stream) != len)
	{
		return EOF;
	}
	else
	{
		return len;
	}
}



long vfprintf(FILE* stream, const char *format, va_list arglist)
{
	long translating	= 0;
	long ret	= 0;
	const	char* p	=0;
	for (p = format;*p != '\0';++p)
	{
		switch (*p)
		{
		case '%':
			if (!translating)
			{
				translating	= 1;
			} 
			else
			{
				if (fputc('%',stream) < 0)
				{
					return EOF;
				}
				++ret;
				translating = 0;
			}
			break;

		case 'd':
			if (translating)	//%d
			{
				char buf[16];
				translating	= 0;
				itoa(va_arg(arglist,long),buf,10);
				if (fputs(buf,stream) < 0)
				{
					return EOF;
				}
				ret+= strlen(buf);
			} 
			else if (fputc('d',stream) < 0)
			{
				return EOF;
			} 
			else
			{
				++ret;
			}
			break;

		case	's':
			if (translating)
			{
				const char *str	= va_arg(arglist,const char*);

				translating	= 0;
				if (fputs(str,stream) < 0)
				{
					return EOF;
				}
				ret +=strlen(str);
			}
			else if (fputc('s',stream) < 0)
			{
				return EOF;
			} 
			else
			{
				++ret;
			}

			break;

		default:
			if (translating)
			{
				translating	= 0;
			}
			if (fputc(*p,stream) <0)
			{
				return EOF;
			} 
			else
			{
				++ret;
			}

			break;
		}
	}
	return ret;
}
/**
 *
 * @param stream
 * @param format
 * @param arglist
 * @return
 */
long _vsnprintf(char* dstr, const char *format, va_list arglist)
{
	long translating	= 0;
	long ret	= 0;
	const	char* p	=0;
	int i = 0;
	for (p = format;*p != '\0';++p)
	{
		switch (*p)
		{
			case '%':
				if (!translating)
				{
					translating	= 1;
				}
				else
				{
					dstr[i++] = '%';
					++ret;
					translating = 0;
				}
				break;

			case 'd':
				if (translating)	//%d
				{
					char buf[16];
					translating	= 0;
					itoa(va_arg(arglist,long),buf,10);
					int len = strlen(buf);
					strcat(dstr,buf);
					i += len;
					ret += len;
				}else
				{
				    dstr[i++] = 'd';
					++ret;
				}
				break;

			case	's':
				if (translating)
				{
					const char *str	= va_arg(arglist,const char*);

					translating	= 0;
					int len = strlen(str);
					strcat(dstr,str);
					i += len;

					ret += len;
				}else
				{
					dstr[i++] = 's';
					++ret;
				}

				break;

			default:
				if (translating)
				{
					translating	= 0;
				}else
				{
					dstr[i++] = *p;
					++ret;
				}

				break;
		}
	}
	return ret;
}
long printf(const char *format,...)
{
	char* arglist;
	asm( "movq %%rbp,%0":"=r"(arglist) );
	arglist -= 0xa8;
	return vfprintf(stdout,format,arglist);
}
long vsnprintf(char* dstr,const char *format,...)
{
	char* arglist;
	asm( "movq %%rbp,%0":"=r"(arglist) );
	arglist -= 0xa0;
	return _vsnprintf(dstr,format,arglist);
}

long fprintf(FILE* stream,const char *format,...)
{
	char* arglist;
	asm( "movq %%rbp,%0":"=r"(arglist) );
	arglist -= 0xa8;
	return vfprintf(stream,format,arglist);
}

