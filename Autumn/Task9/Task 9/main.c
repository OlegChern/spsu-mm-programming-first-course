#include "stdlib.h"
#include "stdio.h"

typedef unsigned char byte;

const int size_memory = 1024 * 1024 * 1024;    // ������ ������� ������.

void* memory;

/*
�������� ������:
����� ������ ������ ���������� ������ ��������������� ��������� ����, 
��������� �� ������� ������� ����� (����� ���� = size / 255 + 2).
��������� �� ������� ����� 0.
� ��������� �������� ����� ����, ������� �������� �����, � �������� ������� (� ������ ������� �� 255, � ������ 255).
�� ����, ���� ������ ���������� ������ ����� 274 �����, �� ������ ����� ��������� ���:
{13 ff 00} --> 19 + 255 = 274
*/

void init() // �������� ������� ������ ����������� ������.
{
	memory = calloc(size_memory, 1);
}

byte* findMemPosition(size_t size, byte* ptr)   // ���� ������ ���������� ������� ������, ��� ���������� ������ ������, � ���������� ��������� �� ������ ���� �������.
{

	if (ptr + size + size / 255 + 2 > (byte*)memory + size_memory)   // �������� �� ����� �� ������� �������.
	{
		return NULL;
	}
	int k = 0;        // k = 0 -> ������� ��������, k = 1 -> ������� ������.
	if (*ptr == 0)
	{
		for (int i = 0; i < size + size / 255 + 2; i++)    // �������� �������.
		{
			if (*ptr != 0)
			{
				k = 1;
				break;
			}
			ptr++;
		}
	}
	else
	{
		k = 1;
	}
	if (k == 0)
	{
		return ptr - size - size / 255 - 2;
	}
	else
	{
		int length = 0;    // ������� �����, ����������� �������.
		length += *ptr;    
		ptr++;

		while (*ptr == 255)
		{
			length += 255;
			ptr++;
		}

		for (int i = 0; i < length + 1; i++)    // ����� �� ����� ����� ���� ��� �������.
		{
			ptr++;
		}
		return findMemPosition(size, ptr);    // ��������� ������.
	}
}

void* myMalloc(size_t size)       // ���������� ��������� �� ������ ������� ���������� ������ (�� �� ������).
{
	byte* ptr = findMemPosition(size, (byte*)memory);
	*ptr = size % 255;       // ������� ������ ��� ����� ������.
	ptr++;
	for (int i = 0; i < size / 255; i++)
	{
		*ptr = 255;
		ptr++;
	}
	ptr++;
	return (void*)ptr;
}

void myFree(void * ptr)       // ������� ���������� ������� �� ����� ��������� (������ � ���������).
{
	byte * nptr = (byte*)ptr;
	nptr--;      // ���������� �� ������� � ������� ����� ����� ���� �������
	nptr--;
	int length = 2;    // 2 - ��� ������������ ����� ������� 1�� � ��������� ������ (����� � ����).
	while (*nptr == 255)
	{
		length += 256;   // 256 - 255 ���� ����� ������ ����� (1).
		nptr--;
	}
	length += *nptr;
	for (int i = 0; i < length; i++)    // ������� ���.
	{
		*nptr++ = 0; 
	}
}

void* myRealloc(void* ptr, size_t size)         // ��������� ������� ������ ������ � ������� � ����� ����� ������ ����� (������ �������).
{
	byte * nptr = (byte*)ptr;
	byte* newPtr = (byte*)myMalloc(size);
	int size2 = 0;
	int k = 2;
	nptr--;
	nptr--;
	while (*nptr == 255)
	{
		k++;
		size2 += 255;
		nptr--;
	}
	size2 += *nptr;        // ������� ����� ������������ ����� ������.
	nptr += k;
	if (size2 > size)         // �������.
	{
		for (int i = 0; i < size; i++)
		{
			newPtr[i] = nptr[i];
		}
	}
	else
	{
		for (int i = 0; i < size2; i++)
		{
			newPtr[i] = nptr[i];
		}
	}

	myFree(ptr);      // ������� ������� �������.
	return (void*)newPtr;
}

int main()
{

	init();

	int* a = (int*)myMalloc(sizeof(int));         // ��������� ������ ��� ����.
	*a = 12;

	byte* b = (byte*)myMalloc(sizeof(byte) * 7);  // ��������� ������ ��� ������� ����������� �����.
	for (int i = 0; i < 7; i++)
	{
		b[i] = i + 1;
	}

	double* c = (double*)myMalloc(sizeof(double) * 3);  // ��������� ������ ��� ������� ������� �����.
	for (int i = 0; i < 3; i++)
	{
		c[i] = i * 4;
	}

	byte* d = (byte*)myMalloc(sizeof(byte));             // ��������� ������ ��� ������������ ����.
	*d = 156;

	b = (byte*)myRealloc(b, sizeof(byte) * 14);           // ���������� ������ ��� ������� ������.
	for (int i = 7; i < 14; i++)
	{
		b[i] = i + 1;
	}

	b = (byte*)myRealloc(b, sizeof(byte) * 10);           // ������� ������ ��� ������� ������

	myFree(a);                                            // ������� ������ ���������� ������.   
	myFree(b);											  //
	myFree(c);											  //
	myFree(d);											  //

	return 0;
}