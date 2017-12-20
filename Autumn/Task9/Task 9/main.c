#include "stdlib.h"
#include "stdio.h"

typedef unsigned char byte;

const int size_memory = 1024 * 1024 * 1024;    // Размер области памяти.

void* memory;

/*
Менеджер памяти:
Перед каждым куском выделенной памяти зарезервированы несколько байт, 
зависящих от размера данного куска (число байт = size / 255 + 2).
Последний из резерва равен 0.
В остальных записано число байт, которое занимфет кусок, в обратном порядке (в первом остаток от 255, в других 255).
То есть, если размер выделяемой памяти равен 274 байта, то резерв будет выглядеть так:
{13 ff 00} --> 19 + 255 = 274
*/

void init() // Выделяет область памяти заполненную нулями.
{
	memory = calloc(size_memory, 1);
}

byte* findMemPosition(size_t size, byte* ptr)   // Ищет первую подходящую область памяти, где поместится данный размер, и возвращает указатель на начало этой области.
{

	if (ptr + size + size / 255 + 2 > (byte*)memory + size_memory)   // Проверка на выход из главной области.
	{
		return NULL;
	}
	int k = 0;        // k = 0 -> область свободна, k = 1 -> область занята.
	if (*ptr == 0)
	{
		for (int i = 0; i < size + size / 255 + 2; i++)    // Проверка области.
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
		int length = 0;    // Подсчет куска, занимающего область.
		length += *ptr;    
		ptr++;

		while (*ptr == 255)
		{
			length += 255;
			ptr++;
		}

		for (int i = 0; i < length + 1; i++)    // Сдвиг на длину куска плюс его резерва.
		{
			ptr++;
		}
		return findMemPosition(size, ptr);    // Проверяем дальше.
	}
}

void* myMalloc(size_t size)       // Возвращает указатель на начало области выделенной памяти (не на резерв).
{
	byte* ptr = findMemPosition(size, (byte*)memory);
	*ptr = size % 255;       // Создаем резерв для куска памяти.
	ptr++;
	for (int i = 0; i < size / 255; i++)
	{
		*ptr = 255;
		ptr++;
	}
	ptr++;
	return (void*)ptr;
}

void myFree(void * ptr)       // Очищает выделенную область по этому указателю (вместе с резервами).
{
	byte * nptr = (byte*)ptr;
	nptr--;      // Сдвигаемся до резерва и считаем длину куска плюс резерва
	nptr--;
	int length = 2;    // 2 - это обязательная длина резерва 1ой и последней ячейки (длина и ноль).
	while (*nptr == 255)
	{
		length += 256;   // 256 - 255 плюс длина своего места (1).
		nptr--;
	}
	length += *nptr;
	for (int i = 0; i < length; i++)    // Очищаем все.
	{
		*nptr++ = 0; 
	}
}

void* myRealloc(void* ptr, size_t size)         // Переносит область памяти вместе с данными в новое место другой длины (старое очищает).
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
	size2 += *nptr;        // Подсчет длины переносимого куска памяти.
	nptr += k;
	if (size2 > size)         // Перенос.
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

	myFree(ptr);      // Очистка прошлой области.
	return (void*)newPtr;
}

int main()
{

	init();

	int* a = (int*)myMalloc(sizeof(int));         // Выделение памяти для инта.
	*a = 12;

	byte* b = (byte*)myMalloc(sizeof(byte) * 7);  // Выделение памяти для массива беззнаковых чаров.
	for (int i = 0; i < 7; i++)
	{
		b[i] = i + 1;
	}

	double* c = (double*)myMalloc(sizeof(double) * 3);  // Выделение памяти для массива дробных чисел.
	for (int i = 0; i < 3; i++)
	{
		c[i] = i * 4;
	}

	byte* d = (byte*)myMalloc(sizeof(byte));             // Выделение памяти для беззнакового чара.
	*d = 156;

	b = (byte*)myRealloc(b, sizeof(byte) * 14);           // Расширение памяти для массива байтов.
	for (int i = 7; i < 14; i++)
	{
		b[i] = i + 1;
	}

	b = (byte*)myRealloc(b, sizeof(byte) * 10);           // Сужение памяти для массива байтов

	myFree(a);                                            // Очистка раннее выделенной памяти.   
	myFree(b);											  //
	myFree(c);											  //
	myFree(d);											  //

	return 0;
}