#pragma once

#include <stdlib.h>
#include <string.h>

#define DEFAULTTABLESIZE 4 // default number of chains in table
#define MAXCHAINSIZE 4 // max number elements in chain

typedef struct
{
	char* key;
	int value;
} HashTableElement;

typedef struct
{
	HashTableElement **elements; // array of pointers to elements
	int elementCount; // count of elements in chain
} HashTableChain;

typedef struct
{
	HashTableChain **chains; // array of pointers to chains
	int chainCount; // count of chains
} HashTable;

// hash key, just using sum of char indices mod size
int hash(HashTable*, char*);

// create new hash table
HashTable *newHashTable();
HashTableChain *addEmptyChain(HashTable*);

// find address of element with given hashKey, returns NULL if key wasn't found
HashTableElement *findElement(HashTableChain*, char*);
int findElementIndex(HashTableChain*, char*);

// rebalance table, just recalculating hashKeys
void rebalance(HashTable*);

// add new key and value
void add(HashTable*, char*, int);
// find value with given key, returns NULL if key wasn't found
int findValue(int*, HashTable*, char*);
// remove key and value
void removeElement(HashTable*, char*);
void printTable(HashTable*);

int hash(HashTable* table, char* key)
{
	int sum = 0;
	while (*key != '\0')
	{
		sum += (int)*key;
		key++;
	}

	return (int)(sum % (table->chainCount));
}

HashTable *newHashTable()
{
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));

	table->chainCount = DEFAULTTABLESIZE;
	table->chains = (HashTableChain**)malloc(sizeof(HashTableChain*) * DEFAULTTABLESIZE);

	for (int i = 0; i < DEFAULTTABLESIZE; i++)
	{
		table->chains[i] = addEmptyChain(table);
	}

	return table;
}

HashTableChain *addEmptyChain(HashTable *table)
{
	HashTableChain *chain = (HashTableChain*)malloc(sizeof(HashTableChain));

	chain->elementCount = 0;
	chain->elements = (HashTableElement**)malloc(sizeof(HashTableElement*) * MAXCHAINSIZE);

	for (int i = 0; i < MAXCHAINSIZE; i++)
	{
		chain->elements[i] = (HashTableElement*)malloc(sizeof(HashTableElement));
	}

	return chain;
}

HashTableElement *findElement(HashTableChain *chain, char* key)
{
	for (int i = 0; i < chain->elementCount; i++)
	{
		HashTableElement *element = chain->elements[i];
		if (strcmp(element->key, key) == 0)
		{
			return element;
		}
	}

	return NULL;
}

int findElementIndex(HashTableChain *chain, char* key)
{
	for (int i = 0; i < chain->elementCount; i++)
	{
		if (strcmp(chain->elements[i]->key, key) == 0)
		{
			return i;
		}
	}

	return -1;
}

void rebalance(HashTable *table)
{
	int prevCount = table->chainCount;
	table->chainCount = (int)(prevCount * 3 / 2);

	// creating temp array of pointer for changing indices
	HashTableChain **temp = (HashTableChain**)malloc(sizeof(HashTableChain*) * table->chainCount);
	for (int i = 0; i < table->chainCount; i++)
	{
		temp[i] = addEmptyChain(table);
	}

	for (int i = 0; i < prevCount; i++)
	{
		HashTableChain *sourceChain = table->chains[i];

		if (sourceChain->elementCount > 0)
		{
			int hashKey = hash(table, sourceChain->elements[0]->key);
			temp[hashKey] = sourceChain;
		}
	}

	for (int i = 0; i < table->chainCount; i++)
	{
		table->chains[i] = temp[i];
	}
}