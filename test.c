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
	//GetSize()�Լ����� ����ϴ� getchar()�Լ��� ���ۿ��� �� ���ھ� ���ڸ� �������� ���̱� ������
	//�ι� ȣ��� �Է��� �ް� �ȴ�..

	printf("fptr = \"%s\"\n", fptr);

	//printf("ffptr = \"%#p\"\n", ffptr);
	//printf("*ffptr[ = \"fstr\"] = \"%#p\"\n", *ffptr);
	//printf("fp->_Placeholder->base = \"%s\"\n", *ffptr);

	return 0;
}