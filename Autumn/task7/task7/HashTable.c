#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "HashTable.h"

typedef struct hashTable
{
	int numberOfElementsInTable;
	int numberOfLists;
	list **listsOfElements;
	int *numberOfElementsInList;
} hashTable;

void buildTable(hashTable **table)
{
	*table = (hashTable*)malloc(sizeof(hashTable));
	(*table)->numberOfElementsInTable = 0;
	(*table)->numberOfLists = length;
	(*table)->listsOfElements = (int*)malloc(length * sizeof(list*));
	(*table)->numberOfElementsInList = malloc(length * sizeof(int*));
	for (int i = 0; i < length; i++)
	{
		(*table)->listsOfElements[i] = NULL;
		(*table)->numberOfElementsInList[i] = 0;
	}
}

int hash(hashTable *table, int key)
{
	return abs(key) % table->numberOfLists;
}

void rebalancing(hashTable **table)
{
	int newNumberOfLists = (*table)->numberOfLists + 1;
	list **newListsOfElement = malloc(newNumberOfLists * sizeof(list*));
	int *newNumberOfElementsInList = malloc(newNumberOfLists * sizeof(int));
	for (int i = 0; i < newNumberOfLists; i++)
	{
		newListsOfElement[i] = NULL;
		newNumberOfElementsInList[i] = 0;
	}
	(*table)->numberOfLists++;

	for (int i = 0; i < (*table)->numberOfLists - 1; i++)
	{
		list *temp = (*table)->listsOfElements[i];
		while (temp != NULL)
		{
			int hashOfKey = hash(*table, temp->key);
			addFirstElement(&newListsOfElement[hashOfKey], temp->key, temp->value);
			temp = temp->next;
		}
	}

	for (int i = 0; i < (*table)->numberOfLists - 1; i++)
	{
		deleteList(&(*table)->listsOfElements[i]);
	}
	
	(*table)->listsOfElements = newListsOfElement;
	(*table)->numberOfElementsInList = newNumberOfElementsInList;
}

int containInTable(hashTable *table, int key)
{
	if (table == NULL)
	{
		return 0;
	}
	int hashOfKey = hash(table, key);
	return contain(table->listsOfElements[hashOfKey], key);
}

int addInTable(hashTable **table, int key, int value)
{
	if (*table == NULL)
	{
		buildTable(*&table);
	}

	int hashOfKey = hash(*table, key);
	if (addFirstElement(&(*table)->listsOfElements[hashOfKey], key, value) == 0)
	{
		return 0;
	}
	
	(*table)->numberOfElementsInList[hashOfKey]++;
	(*table)->numberOfElementsInTable++;
	
	if (((*table)->numberOfElementsInList[hashOfKey] > ((*table)->numberOfElementsInTable / 2)) && ((*table)->numberOfElementsInList[hashOfKey] >= 3))
	{
		rebalancing(*&table);
	}
	return 1;
}

int deleteFromTable(hashTable **table, int key)
{
	if (*table == NULL)
	{
		return 0;
	}

	int hashOfKey = hash(*table, key);
	if (deleteElement(&(*table)->listsOfElements[hashOfKey], key) == 0)
	{
		return 0;
	}
	
	(*table)->numberOfElementsInList[hashOfKey]--;
	(*table)->numberOfElementsInTable--;
	return 1;
}

int getValue(hashTable *table, int key, int *correct)
{
	if (table == NULL)
	{
		*correct = 0;
		return 0;
	}

	int hashOfKey = hash(table, key);
	return getValueByKey(table->listsOfElements[hashOfKey], key, *&correct);
}

void printTable(hashTable *table)
{
	if (table == NULL)
	{
		return;
	}

	for (int i = 0; i < table->numberOfLists; i++)
	{
		printList(table->listsOfElements[i]);
	}
}

void deleteTable(hashTable **table)
{
	if (*table == NULL)
	{
		return;
	}
	for (int i = 0; i < (*table)->numberOfLists; i++)
	{
		deleteList(&(*table)->listsOfElements[i]);
	}
	free(*table);
}


void addElementsForTestTable(hashTable **table)
{
	addInTable(*&table, 1, 11);
	addInTable(*&table, 2, 12);
	addInTable(*&table, 3, 13);
	addInTable(*&table, 4, 14);
	addInTable(*&table, 5, 15);
	addInTable(*&table, 6, 16);
	addInTable(*&table, 7, 17);
	addInTable(*&table, 8, 18);
	addInTable(*&table, 9, 19);
	addInTable(*&table, 10, 10);
}

int testTableAddElement()
{
	hashTable *table = NULL;
	addElementsForTestTable(&table);

	if (containInTable(table, 1) && containInTable(table, 2) && containInTable(table, 3) && containInTable(table, 4) && containInTable(table, 5)
		&& containInTable(table, 6) && containInTable(table, 7) && containInTable(table, 8) && containInTable(table, 9) && containInTable(table, 10))
	{
		deleteTable(&table);
		return 1;
	}
	deleteTable(&table);
	return 0;
}

int testTableContain()
{
	hashTable *table = NULL;
	addElementsForTestTable(&table);

	if (containInTable(table, 1) && containInTable(table, 2) && containInTable(table, 5) && containInTable(table, 7) && containInTable(table, 9)
		&& (!containInTable(table, 11)) && (!containInTable(table, 12)))
	{
		deleteTable(&table);
		return 1;
	}
	deleteTable(&table);
	return 0;
}

int testTableDeleteElement()
{
	hashTable *table = NULL;
	addElementsForTestTable(&table);

	if (deleteFromTable(&table, 11))
	{
		deleteTable(&table);
		return 0;
	}

	if ((!deleteFromTable(&table, 5)) || (!deleteFromTable(&table, 9)) || (!deleteFromTable(&table, 7)))
	{
		deleteTable(&table);
		return 0;
	}

	if (containInTable(table, 5) || containInTable(table, 9) || containInTable(table, 7))
	{
		deleteTable(&table);
		return 0;
	}
	deleteTable(&table);
	return 1;
}

int getValueByKeyTestTable()
{
	hashTable *table = NULL;
	addElementsForTestTable(&table);
	int correct = -1;

	if ((getValue(table, 7, &correct) != 17) || (correct != 1))
	{
		deleteTable(&table);
		return 0;
	}

	if ((getValue(table, 11, &correct) != 0) || (correct != 0))
	{
		deleteTable(&table);
		return 0;
	}

	deleteTable(&table);
	return 1;
}

int rebalancingTest()
{
	hashTable *table = NULL;
	addInTable(&table, 1, 11);
	addInTable(&table, 2, 12);
	addInTable(&table, 3, 13);
	addInTable(&table, 5, 15);
	addInTable(&table, 8, 18);
	
	if ((table->numberOfLists == 4) && (contain(table->listsOfElements[1], 5)) && (!contain(table->listsOfElements[2], 5)) && (contain(table->listsOfElements[0], 8)))
	{
		deleteTable(&table);
		return 1;
	}
	deleteTable(&table);
	return 0;
}

int testTable()
{
	return (testTableAddElement() && testTableContain() && testTableDeleteElement() && getValueByKeyTestTable() && rebalancingTest());
}