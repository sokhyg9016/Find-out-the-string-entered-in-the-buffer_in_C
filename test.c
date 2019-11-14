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
	//char** ffptr = (char**)(&(fp->_Placeholder) + 1);
	char* fptr = NULL;

	//INPUT NULL
	//*(*(ffptr) + GetSize()) = '\0';
	getchar();
	fptr = *((char**)&fp->_Placeholder + 1);

	fptr[GetSize()] = '\0';

	//*Caution! 
	//GetSize()함수에서 사용하는 getchar()함수는 버퍼에서 한 글자씩 문자를 가져오는 것이기 때문에
	//두번 호출시 입력을 받게 된다..

	printf("fptr = \"%s\"\n", fptr);

	//printf("ffptr = \"%#p\"\n", ffptr);
	//printf("*ffptr[ = \"fstr\"] = \"%#p\"\n", *ffptr);
	//printf("fp->_Placeholder->base = \"%s\"\n", *ffptr);

	return 0;
}