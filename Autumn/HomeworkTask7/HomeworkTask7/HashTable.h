#pragma once

#define BINSIZE 10 // max number elements in chain

typedef struct
{
	char* key;
	int value;
} HashTableElement;

typedef struct
{
	int hashKey;
	HashTableElement **elements; // array of pointers to elements
	int elementCount; // count of elements in chain
} HashTableChain;

typedef struct
{
	HashTableChain **chains; // array of pointers to chains
	int chainCount; // count of chains
} HashTable;

// hash key, just using sum of char indexes mod size
int hash(HashTable*, char*);

// create new hash table
HashTable *newHashTable();
HashTableChain *addEmptyChain(HashTable*);
HashTableElement *addEmptyElement(HashTableChain*);

// find address of chain with given hashKey, returns NULL if key wasn't found
HashTableChain *findChain(HashTable*, int);
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

int hash(HashTable* table, char* key)
{
	int sum = 0;
	while (*key != '\0')
	{
		sum += (int)*key;
		key++;
	}

	return sum % (table->chainCount);
}

HashTable *newHashTable()
{
	HashTable *table = (HashTable*)malloc(sizeof(HashTable));
	table->chains = (HashTableChain**)malloc(sizeof(HashTableChain*));
	table->chainCount = 0;

	return table;
}

HashTableChain *addEmptyChain(HashTable *table)
{
	table->chainCount++;

	HashTableChain *chain = (HashTableChain*)malloc(sizeof(HashTableChain));
	chain->elementCount = 0;

	return chain;
}

HashTableElement *addEmptyElement(HashTableChain *chain)
{
	chain->elementCount++;

	HashTableElement *element = (HashTableElement*)malloc(sizeof(HashTableElement));

	return element;
}

HashTableChain *findChain(HashTable *table, int hashKey)
{
	for (int i = 0; i < table->chainCount; i++)
	{
		HashTableChain *chain = table->chains[i];
		if (chain->hashKey == hashKey)
		{
			return chain;
		}
	}

	return NULL;
}

HashTableElement *findElement(HashTableChain *chain, char* key)
{
	for (int i = 0; i < chain->elementCount; i++)
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
	for (int i = 0; i < table->chainCount; i++)
	{
		HashTableChain *chain = table->chains[i];

		// if there is at least one element
		if (chain->elementCount > 0)
		{
			// new hashKey for current chain
			chain->hashKey = hash(table, chain->elements[0]->key);
		}
	}
}