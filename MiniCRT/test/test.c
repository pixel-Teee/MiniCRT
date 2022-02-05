#include "../MiniCRT/minicrt.h"

int main(int argc, char* argv[])
{
	int i;
	FILE* fp;
	char** v = Malloc(argc * sizeof(char*));

	for (i = 0; i < argc; ++i)
	{
		v[i] = Malloc(Strlen(argv[i]) + 1);
		Strcpy(v[i], argv[i]);
	}

	fp = fopen("test.txt", "w");
	for (i = 0; i < argc; ++i)
	{
		int len = Strlen(v[i]);
		Printf("%d", len);
		fwrite(&len, 1, sizeof(int), fp);
		fwrite(v[i], 1, len, fp);
	}

	fclose(fp);

	/*
	fp = fopen("test.txt", "r");
	for (i = 0; i < argc; ++i)
	{
		int len;
		char* buf;
		fread(&len, 1, sizeof(int), fp);
		buf = Malloc(len + 1);
		fread(buf, 1, len, fp);
		buf[len] = '\0';
		Printf("%d %s\n", len, buf);
		Free(buf);
		Free(v[i]);
	}
	fclose(fp);
	*/
}