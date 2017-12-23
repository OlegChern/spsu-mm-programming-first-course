#include "stdio.h"
#include "stdlib.h"
#include "header.h"

void addValue(listElement** head, const char* string)            // ���������� �������� � ������
{
	if (*head == NULL)
	{
		*head = (listElement*)malloc(sizeof(listElement));
		(*head)->string = string;
		(*head)->pointerNext = NULL;
	}
	else
	{
		listElement* new = (listElement*)malloc(sizeof(listElement));
		new->string = string;
		new->pointerNext = *head;
		*head = new;
	}
}

int deleteValue(listElement** head, const char* string)             // �������� ������� �������� ������ � ������ ���������
{
	if (*head == NULL)
	{
		return 0;
	}
	else
	{
		listElement* pointer = *head;
		while (pointer->string != string)
		{
			if (pointer->pointerNext == NULL)
			{
				return 0;
			}
			pointer = pointer->pointerNext;
		}
		if (pointer->pointerNext == NULL)
		{
			free(pointer);
			*head = NULL;
			return 1;
		}
		else
		{
			listElement* nextPointer = pointer->pointerNext;
			pointer->string = nextPointer->string;
			pointer->pointerNext = nextPointer->pointerNext;
			free(nextPointer);
			return 1;
		}
	}
}

int isBelong(listElement** head, const char* string)              // ���������� 1, ���� ������ ������� ������������ � ������, ����� 0
{
	if (*head == NULL)
	{
		return 0;
	}
	else
	{
		listElement* pointer = *head;
		while (pointer->string != string)
		{
			if (pointer->pointerNext == NULL)
			{
				return 0;
			}
			pointer = pointer->pointerNext;
		}
		return 1;
	}
}

void deleteList(listElement** head)                   // �������� ������
{
	listElement* pointer = *head;
	while (pointer != NULL)
	{
		pointer = pointer->pointerNext;
		free(*head);
		*head = pointer;
	}
}