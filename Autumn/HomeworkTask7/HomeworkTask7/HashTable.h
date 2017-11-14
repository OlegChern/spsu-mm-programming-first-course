#pragma once

#include <stdlib.h>

#define DEFAULTTABLESIZE 16 // default number of chains in table
#define MAXBINSIZE 4 // max number elements in chain

typedef unsigned int UINT;

typedef struct
{
	char* key;
	int value;
} HashTableElement;

typedef struct
{
	UINT hashKey;
	HashTableElement **elements; // array of pointers to elements
	UINT elementCount; // count of elements in chain
} HashTableChain;

typedef struct
{
	HashTableChain **chains; // array of pointers to chains
	UINT chainCount; // count of chains
} HashTable;

// hash key, just using sum of char indices mod size
UINT hash(HashTable*, char*);

// create new hash table
HashTable *newHashTable();
HashTableChain *addEmptyChain(HashTable*);
HashTableElement *addEmptyElement(HashTableChain*);

// find address of chain with given hashKey, returns NULL if key wasn't found
HashTableChain *findChain(HashTable*, UINT);
// find address of element with given hashKey, returns NULL if key wasn't found
HashTableElement *findElement(HashTableChain*, char*);

// rebalance table, just recalculating hashKeys
void rebalance(HashTable*);

// add new key and value
void add(HashTable*, char*, int);
// find value with given key, returns NULL if key wasn't found
int *findValue(HashTable*, char*);
// remove key and value
void removeElement(HashTable*, char*);

UINT hash(HashTable* table, char* key)
{
	UINT sum = 0;
	while (*key != '\0')
	{
		sum += (int)*key;
		key++;
	}

	return (UINT)(sum % (table->chainCount));
}

HashTable *newHashTable()
{
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));
	table->chainCount = DEFAULTTABLESIZE;
	table->chains = (HashTableChain**)malloc(sizeof(HashTableChain*) * DEFAULTTABLESIZE);
	for (UINT i = 0; i < DEFAULTTABLESIZE; i++)
	{
		table->chains[i] = addEmptyChain(table);
	}

	return table;
}

HashTableChain *addEmptyChain(HashTable *table)
{
	HashTableChain *chain = (HashTableChain*)malloc(sizeof(HashTableChain));
	chain->elementCount = 0;

	chain->elements = (HashTableElement**)malloc(sizeof(HashTableElement*) * MAXBINSIZE);
	for (UINT i = 0; i < MAXBINSIZE; i++)
	{
		chain->elements[i] = addEmptyElement(chain);
	}

	return chain;
}

HashTableElement *addEmptyElement(HashTableChain *chain)
{
	HashTableElement *element = (HashTableElement*)malloc(sizeof(HashTableElement));
	chain->elements[chain->elementCount] = element;

	return element;
}

HashTableChain *findChain(HashTable *table, UINT hashKey)
{
	for (UINT i = 0; i < table->chainCount; i++) // DELETE this
	{
		HashTableChain *chain = table->chains[i];
		if (chain != NULL && chain->elementCount > 0)
		{
			if (chain->hashKey == hashKey) // DELETE this
			{
				return chain;
			}
		}
	}
	
	return NULL;
}

HashTableElement *findElement(HashTableChain *chain, char* key)
{
	for (UINT i = 0; i < chain->elementCount; i++)
	{
		HashTableElement *element = chain->elements[i];
		if (element->key == key)
		{
			return element;
		}
	}

	return NULL;
}

void rebalance(HashTable *table)
{
	UINT prevCount = table->chainCount;
	table->chainCount = (table->chainCount * 3 / 2);

	//table->chains = (HashTableChain**)realloc(sizeof(HashTableChain*) * table->chainCount);

	// creating temp array of pointer for changing indices
	HashTableChain **temp = (HashTableChain**)malloc(sizeof(HashTableChain*) * table->chainCount);

	for (UINT i = 0; i < table->chainCount; i++)
	{
		HashTableChain *chain; 
		
		if (i < prevCount)
		{
			chain = table->chains[i];
		}
		else
		{
			chain = addEmptyChain(table);
			//table->chains[i] = chain;
		}

		temp[i] = (HashTableChain*)malloc(sizeof(HashTableChain));

		if (chain != NULL)
		{
			// if there is at least one element recalculating hash key
			if (chain->elementCount > 0)
			{
				UINT hashKey = hash(table, chain->elements[0]->key);
				temp[i] = table->chains[hashKey];
				temp[i]->hashKey = hashKey;
			}
		}
		else
		{
			temp[i] = NULL;
		}
	}

	table->chains = temp;
}