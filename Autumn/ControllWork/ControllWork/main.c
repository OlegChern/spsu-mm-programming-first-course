#include "stdlib.h"
#include "stdio.h"

struct listElement
{
	int value;
	struct listElement* next;
};

typedef struct listElement listElement;


struct list
{
	struct listElement* readPtr;
	struct listElement* writePtr;
};

typedef struct list list;

list* initList(int length)
{
	list* newList = (list*)malloc(sizeof(list));
	listElement* e = (listElement*)malloc(sizeof(listElement));
	listElement* e1 = e;
	for (int i = 0; i < length - 1; i++)
	{
		e->value = 0;
		e->next = (listElement*)malloc(sizeof(listElement));
		e = e->next;
	}
	e->value = 0;
	e->next = e1;
	newList->readPtr = e1;
	newList->writePtr = e1;
	return newList;
}

void add(list* listA, int value)
{
	list* list = listA;
	listElement * prevElement = NULL;
	if (list->writePtr->next == list->readPtr)
	{
		prevElement = list->writePtr;
	}

	list->writePtr->value = value;
	list->writePtr = list->writePtr->next;
	if (list->writePtr == list->readPtr)
	{
		list->writePtr = (listElement*)malloc(sizeof(listElement));
		list->writePtr->value = 0;
		list->writePtr->next = list->readPtr;
		prevElement->next = list->writePtr;
	}
}

int get(list* listA)
{
	list* list = listA;
	int value = list->readPtr->value;
	list->readPtr = list->readPtr->next;
	return value;
}

int main()
{
	list* listBuf = NULL;
	int length = 2;
	listBuf = initList(length);
	
	add(listBuf, 3);
	add(listBuf, 4);
	int a = get(listBuf);
	add(listBuf, 5);
	int b = get(listBuf);
	int c = get(listBuf);
	add(listBuf, 6);
	add(listBuf, 7);
	add(listBuf, 8);
	int d = get(listBuf);
	add(listBuf, 9);
	int e = get(listBuf);
	int f = get(listBuf);
	int g = get(listBuf);
	int h = get(listBuf);
	int i = get(listBuf);

	printf("%d %d %d %d %d %d %d %d %d", a, b, c, d, e, f, g, h, i);  // Вывод полученных значений

	_getch();
	return 0;
}
