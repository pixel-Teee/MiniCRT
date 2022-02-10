#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif

//malloc
#ifndef NULL
#define NULL (0)
#endif

void Free(void* ptr);
void* Malloc(unsigned size);
static int brk(void* end_data_segment);
int mini_crt_heap_init();

//×Ö·û´®
char* Itoa(int n, char* str, int radix);
int Strcmp(const char* src, const char* dst);
char* Strcpy(char *dest, const char* src);
unsigned Strlen(const char* str);


//ÎÄ¼þÓëIO
typedef int FILE;

#define EOF (-1)

#ifdef WIN32
#define stdin ((FILE*)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout ((FILE*)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr ((FILE*)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)
#endif

int mini_crt_io_init();
FILE* fopen(const char* filename, const char* mode);
int fread(void *buffer, int size, int count, FILE* stream);
int fwrite(const void* buffer, int size, int count, FILE* stream);
int fclose(FILE* fp);
int fseek(FILE* fp, int offset, int set);

//printf
int Fputc(int c, FILE* stream);
int Fputs(const char* str, FILE* stream);
int Printf(const char* format, ...);
int Fprintf(FILE* stream, const char* format, ...);

void do_global_ctors();
void mini_crt_call_exit_routine();

//atexit
typedef void (*atexit_func_t)(void);
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif

#endif
