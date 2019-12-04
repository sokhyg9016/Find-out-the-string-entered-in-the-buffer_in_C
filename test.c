#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<memory.h>

int GetSize()
{
	int i = 0;
	while (getchar() != '\n')
	{
		i++;
	}
	return i;
}

int main()
{
	FILE* fp = stdin;
	char* fptr = NULL;

	getchar();
	fptr = *((char**)& fp->_Placeholder + 1);

	fptr[GetSize()] = '\0';

	printf("fptr = \"%s\"\n", fptr);

	return 0;
}