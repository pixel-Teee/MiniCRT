#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* agrv[]);
//heap init
int mini_crt_heap_init();

//error && exit
void crt_fatal_error(const char* msg);
void Exit(int);

void mini_crt_entry(void)
{
	int ret;

#ifdef WIN32
	int flag = 0;
	int argc = 0;
	char* argv[16];//最多16个参数
	char* c1 = GetCommandLineA();

	//解释命令行
	argv[0] = c1;
	++argc;
	// "F:/Test.exe" 123 456 789
	// divide these to F:/Test.exe 123 456 789
	while (*c1)
	{
		if (*c1 == '\"')
		{
			if(flag == 0) flag = 1;
			else flag = 0;
		}
		else if (*c1 == ' ' && flag == 0)
		{
			if (*(c1 + 1))
			{
				argv[argc] = c1 + 1;
				++argc;
			}
			*c1 = '\0';
		}
		++c1;
	}
#else
	int argc;
	char** argv;

	char* ebp_reg = 0;
	//ebp_reg = %ebp

	asm(
	"movl %%ebp, %0 \n"
	:"=r"(ebp_reg));

	argc = *(int*)(ebp_reg + 4);
	argv = (char**)(ebp_reg + 8);
#endif

	if (!mini_crt_heap_init())
	{
		crt_fatal_error("heap initialize failed");
	}
	
	
	if (!mini_crt_io_init())
	{
		crt_fatal_error("IO initialize failed");
	}

	do_global_ctors();
	
	ret = main(argc, argv);
	Exit(ret);
}

void Exit(int exitCode)
{
	mini_crt_call_exit_routine();
#ifdef WIN32
	ExitProcess(exitCode);
#else
	//hlt pause the process
	//m exitcode memory variable
	//ebx store the error code
	asm("movl %0, %%ebx \n\t"
		"movl $1, %%eax \n\t"
		"int $0x80 \n\t"
		"hlt \n\t"::"m"(exitCode));
#endif
}

static void crt_fatal_error(const char* msg)
{
	Exit(1);
}

