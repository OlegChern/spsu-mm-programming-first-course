#include <stdio.h>
#include <stdlib.h>
#include "List.h"



int contain(list *first, int keyForSearch)
{
	if (first == NULL)
	{
		return 0;
	}
	
	list *temp = first;
	while (temp->key != keyForSearch)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int addFirstElement(list **first, int key, int value)
{
	if (contain(*first, key))
	{
		return 0;
	}

	list *newFirst = malloc(sizeof(list));
	newFirst->next = *first;
	newFirst->value = value;
	newFirst->key = key;

	*first = newFirst;
	return 1;
}

void deleteFirst(list **first)
{
	if (*first == NULL)
	{
		return;
	}

	list *oldFirst = *first;
	*first = (*first)->next;
	free(oldFirst);
}

int deleteElement(list **first, int key)
{
	if (*first == NULL)
	{
		return 0;
	}

	if (!contain(*first, key))
	{
		return 0;
	}

	if ((*first)->key == key)
	{
		deleteFirst(*&first);
		return 1;
	}

	list *temp = *first;
	while ((temp->next != NULL) && (temp->next->key != key))
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		return 0;
	}
	list *oldElement = temp->next;
	list *elementNext = temp->next;
	temp->next = elementNext->next;
	free(oldElement);

	return 1;
}

int getValueByKey(list *first, int key, int *correct)
{
	if (first == NULL)
	{
		*correct = 0;
		return 0;
	}
	
	list *temp = first;

	while (temp->key != key)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
		else
		{
			*correct = 0;
			return 0;
		}
	}
	*correct = 1;
	return temp->value;
}

void deleteList(list **first)
{
	while (*first != NULL)
	{
		deleteFirst(*&first);
	}
}

void printList(list *first)
{
	if (first == NULL)
	{
		return;
	}

	list *temp = first;
	while (temp->next != NULL)
	{
		printf("%d", temp->key);
		putchar('-');
		printf("%d", temp->value);
		putchar(' ');
		temp = temp->next;
	}
	printf("%d", temp->key);
	putchar('-');
	printf("%d", temp->value);
	putchar('\n');
}



void addElementsForTest(list **list)
{
	addFirstElement(*&list, 1, 11);
	addFirstElement(*&list, 2, 12);
	addFirstElement(*&list, 3, 13);
	addFirstElement(*&list, 4, 14);
	addFirstElement(*&list, 5, 15);
}

int testAddElement()
{
	list *list = NULL;
	addElementsForTest(&list);

	if (contain(list, 1) && contain(list, 2) && contain(list, 3) && contain(list, 4) && contain(list, 5))
	{
		deleteList(&list);
		return 1;
	}
	deleteList(&list);
	return 0;
}

int testContain()
{
	list *list = NULL;
	addElementsForTest(&list);

	if (contain(list, 1) && contain(list, 3) && contain(list, 5) && (!contain(list, 6)) && (!contain(list, 7)))
	{
		deleteList(&list);
		return 1;
	}
	deleteList(&list);
	return 0;
}

int testDeleteElement()
{
	list *list = NULL;
	addElementsForTest(&list);

	if (deleteElement(&list, 6))
	{
		deleteList(&list);
		return 0;
	}

	if ((!deleteElement(&list, 5)) || (!deleteElement(&list, 3)) || (!deleteElement(&list, 1)))
	{
		deleteList(&list);
		return 0;
	}

	if (contain(list, 1) || contain(list, 3) || contain(list, 1))
	{
		deleteList(&list);
		return 0;
	}
	deleteList(&list);
	return 1;
}

int getValueByKeyTest()
{
	list *list = NULL;
	addElementsForTest(&list);
	int correct = -1;

	if ((getValueByKey(list, 2, &correct) != 12) || (correct != 1))
	{
		deleteList(&list);
		return 0;
	}

	if ((getValueByKey(list, 6, &correct) != 0) || (correct != 0))
	{
		deleteList(&list);
		return 0;
	}

	deleteList(&list);
	return 1;
}

int testList()
{
	return (testAddElement() && testContain() && testDeleteElement() && getValueByKeyTest());
}
