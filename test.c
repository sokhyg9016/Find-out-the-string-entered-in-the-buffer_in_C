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
	//void** fptr = &(fp->_Placeholder);
	char** ffptr = (char**)(&(fp->_Placeholder) + 1);
	//char* fstr = NULL;

	//BUFFER INPUT
	//getchar();

	//SIZE Check
	//printf("Size of Input String in Buffer = %d\n", GetSize());
	
	//Point to String in Buffer
	//fstr = *ffptr;

	//INPUT NULL
	//fstr[GetSize() + 1] = '\0';
	*(*(ffptr) + GetSize()) = '\0';

	//*Caution! 
	//GetSize()�Լ����� ����ϴ� getchar()�Լ��� ���ۿ��� �� ���ھ� ���ڸ� �������� ���̱� ������
	//�ι� ȣ��� �Է��� �ް� �ȴ�..

	//printf("\n\nfp->_Placeholder->base's Address = \"%#p\"\n", (char*)(fptr + 1));
	printf("ffptr = \"%#p\"\n", ffptr);
	printf("*ffptr[ = \"fstr\"] = \"%#p\"\n", *ffptr);
	printf("fp->_Placeholder->base = \"%s\"\n", *ffptr);
	//printf("fp->_Placeholder->base = \"%s\"\n", fstr);

	return 0;
}