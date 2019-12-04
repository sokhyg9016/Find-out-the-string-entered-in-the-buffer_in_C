﻿# Find-out-the-string-entered-in-the-buffer_in_C<br>

| **작성일**       | **키워드**           |  **참고**|
| ------------- |:-------------:|:-------------:| 
| 2019.04.04     | `C` `FILE I/O` `Pointer` | - |

## Points
1.  FILE 포인터로 ```stdin```을 가리킨 상태에서 포인터를 이용하여 메모리 주소에 접근해 입력한 문자열을 디버그 모드에서 확인해보자.

1. 작업 환경: `Visual Stdio 2017` 이며, 2017버전은 현재(작성일, 2019.04.04) FILE 포인터의 구조체 맴버를 볼 수 없기에디버깅을 통해 **_ptr** 과 **_base** 등의 대략적인 위치를 알아냄.

1. 이 프로그램은 두 가지 포인터를 이용하여 입력한 문자열을 확인해 보고, 정상적인 출력을 위해 문자열 끝에 `NULL`을 넣고 난뒤에 출력해보는 프로그램이다.

1. 이 문제의 핵심은 포인터를 얼마만큼 잘 이해하고 활용할 수 있느냐이다. 처음 FILE 포인터 `fp`는 `stdin`을 가리키고 있으며, 이때 또다른 포인터를 사용하여 fp의 구조체 맴버인 `Placeholder`의 주소값을 가리키게 함.

1. 중요한 점은 이 상태에서 **base** 포인터가 어디에 위치하며, 또한 그 위치를 알았을때 포인터를 이용해 저장된 문자열이 저장되어 있는 주소로 어떻게 접근을 할 것이고, 또 어떻게 출력을 할 것인가 입니다.

1. 주소 또한 데이터형을 가지고 있으며, 형 변환이 가능하다는 점을 이용함. 특정 요소에 접근하고자 할 때 이러한 점을 잘 염두해 두고 접근할 것

<br>

## [2019.04.04] 왜 ```char*```으로 접근할 수 없는 것인가?

소스 코드에서 왜 (char**)으로 형변환후에 출력했는가 하면, 디버그를 해보면 알 수 있듯이 원래부터 stdin에 존재하는 베이스포인터의 타입은 void** 입니다.

base포인터는 현재 입력된 값이 저장된 주소를 저장하고 있으며 문자열은 const char*, 즉 문자열의 주소를 저장하고 있는 포인터는 void** 과 같은 이중 포인터가 되어야 합니다. 따라서 만약 char* 을 통해 접근하고자 했다면, 우리는 base포인터로 밖에 접근하지 못하며, `char* sch = (char*)base_p;`이후 `*sch`을 해도 base포인터에 저장된 문자열이 저장된 곳의 주소값을 단순히 문자 형식으로만(char*을 역참조하여 출력하려면 char형이므로) 출력해줄 뿐입니다.

즉, 원래부터가 base 포인터의 타입은 2중 포인터이기 때문에 우리가 접근하여 문자열을 건드리고 싶다면 그 타입에 맞게 접근해야 원하고자 하는 답을 찾을 수 있다...

<br>

## [수정: 2019.12.03] ```char*``` 으로 접근 가능하다!

이전에 작성한 내용은 즉, 베이스 포인터의 타입은 ```void**```이기 때문에 문자열이 저장된 곳의 시작 주소 값을 이용하기 위해서는 ```char*```이 아닌 ```char**```으로 작성해야 한다고 했다. 왜냐하면 필자는 base 포인터 타입은 2중 포인터이고, 그에 맞게 적절히 형 변환을 시켜줘야 정확한 값이 나온다고 생각했기 때문이다.

하지만 착각할 수 있는 것이 만약 코드에서 ```FILE* fp = stdin;```과 같은 식으로 작성했다면, ```fp```는 ```_Placeholder```라는 것의 주소값을 저장하고 있기 때문이다. 또한 이 ```_Placeholder```라는 녀석이 바로 현재 버퍼의 위치에 대한 주소값을 저장하고 있는 포인터이다. 

이때 타입 ```FILE```의 구조는 다음과 같다.

> corecrt_wstdio.h
```C

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Stream I/O Declarations Required by this Header
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#ifndef _FILE_DEFINED
    #define _FILE_DEFINED
    typedef struct _iobuf
    {
        void* _Placeholder;
    } FILE;
#endif
```
즉, *base*와 같은 역할을 하는 `_Placeholder`의 타입은 ```void* ```이라는 것이다.
아마 필자는 작성 당시 개념에 대해 햇갈렸던 것 같다. 이때 메모리 구조로 살펴보자면,

|**variable name**|**variable address**|**variable content**|**>**|**variable address**|**variable content**|**Translation**|
| ------------- |:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
|```&fp->_Placeholder```|0x0FE74A28|f1 1f 8c 00|>|f1 1f 8c 00|65 6c 6c 6f 20 57 6f 72 6c 64 21 0a 0a|ello World!..|
|```&fp->_Placeholder+1```|0x0FE74A2C|f0 1f 8c 00|>|f0 1f 8c 00|48 65 6c 6c 6f 20 57 6f 72 6c 64 21 0a 0a|Hello World!..|
|...|...|...|>|...|...|...|

따라서 **f0 1f 8c 00** 즉, ```008c1ff0```이 바로 우리가 입력한 문자열이 저장된 곳의 시작주소라는 것이다.
이때 ```&fp->_Placeholder + 1```이 저장하고 있는 ```008c1ff0```라는 값의 타입은 ```void*```이므로,  이를 ```char*```으로 바꾸어 사용할 수 있는 것이다.

예를 들어 우리가 코드에서 문자열을 ```Hello World!```와 같이 입력한다면,
```C
FILE* fp = stdin;
char* fptr = NULL;
...
getchar(); // input "Hello World!"
fptr = (char*)(&fp->_Placeholder + 1);
```
우리는 위와 같이 사용할 수 있다. 이때 마지막 줄을 통해 우리는 ```fptr```이 새롭게 버퍼에 입력된 문자열의 시작주소를 가리키고 있음을 알 수 있다.

<br>

## 코드 수정 -> ```main.c``` (2019.12.03)

위와 같은 내용을 기반으로 코드를 수정했다. 전체 코드는 아래와 같다.

```C

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

```
