#include "minicrt.h"

int Fputc(int c, FILE* stream)
{
	if(fwrite(&c, 1, 1, stream) != 1)
		return EOF;
	else
		return c;
}

int Fputs(const char* str, FILE* stream)
{
	int len = Strlen(str);
	if(fwrite(str, 1, len, stream) != len)
		return EOF;
	else
		return len;
}

#ifndef WIN32
#define va_list char*
#define va_start(ap, arg) (ap=(va_list)&arg + sizeof(arg))
#define va_arg(ap, t) (*(*t)((ap += sizeof(t)) - sizeof(t)))
#define va_end(ap) (ap=(va_list)0)
#else
#include <windows.h>
#endif

int Vfprintf(FILE* stream, const char* format, va_list arglist)
{
	int translating = 0;
	int ret = 0;
	const char* p = 0;
	for (p = format; *p != '\0'; ++p)
	{
		switch (*p)
		{
		case '%':
			if(!translating)
				translating = 1;
			else
			{
				if(Fputc('%', stream) < 0)
					return EOF;
				++ret;
				translating = 0;
			}
			break;
		case 'd':
			if (translating)
			{
				char buf[16];
				translating = 0;
				Itoa(va_arg(arglist, int), buf, 10);
				if(Fputs(buf, stream) < 0)
					return EOF;
				ret += Strlen(buf);
			}
			else if(Fputc('d', stream) < 0)
				return EOF;
			else
				++ret;
			break;
		case 's':
			if (translating)
			{
				const char* str = va_arg(arglist, const char*);
				translating = 0;
				if(Fputs(str, stream) < 0)
					return EOF;
				ret += Strlen(str);
			}
			else if(Fputc('s', stream) < 0)
				return EOF;
			else
				++ret;
			break;
		default:
			if(translating)
				translating = 0;
			if(Fputc(*p, stream) < 0)
				return EOF;
			else
				++ret;
			break;
		}
	}
	return ret;
}

int Printf(const char* format, ...)
{
	va_list(arglist);
	va_start(arglist, format);
	return Vfprintf(stdout, format, arglist);
}

int Fprintf(FILE* stream, const char* format, ...)
{
	va_list(arglist);
	va_start(arglist, format);
	return Vfprintf(stream, format, arglist);
}

 