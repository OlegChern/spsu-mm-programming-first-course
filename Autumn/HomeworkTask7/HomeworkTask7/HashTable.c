#include <stdio.h>
#include "HashTable.h"

// add new key and value
void add(HashTable *table, char* key, int value)
{
	UINT hashKey = hash(table, key);
	HashTableChain *chain = findChain(table, hashKey);

	if (chain == NULL) // wasn't found
	{
		chain = addEmptyChain(table);
		chain->hashKey = hashKey;
		table->chains[hashKey] = chain;
	}

	HashTableElement *element = addEmptyElement(chain);
	element->value = value;
	element->key = key;

	chain->elementCount++;

	if (chain->elementCount >= MAXBINSIZE)
	{
		rebalance(table);
	}
}

// find pointer to value with given key, returns NULL if key wasn't found
int *findValue(HashTable *table, char* key)
{
	HashTableChain *chain = findChain(table, hash(table, key));
	if (chain != NULL)
	{
		HashTableElement *element = findElement(chain, key);
		if (element != NULL) // was found
		{
			return &(element->value);
		}
	}

	return NULL;
}

// remove key and value
void removeElement(HashTable *table, char* key)
{
	HashTableChain *chain = findChain(table, hash(table, key));
	if (chain != NULL)
	{
		HashTableElement *element = findElement(chain, key);
		if (element != NULL) // was found
		{
			element = NULL;
			free(element);
		}
	}
}

void printTable(HashTable* table)
{
	for (UINT i = 0; i < table->chainCount; i++)
	{
		HashTableChain *chain = table->chains[i];

		if (chain != NULL)
		{
			printf("\n");
			
			for (UINT j = 0; j < chain->elementCount; j++)
			{
				//if (chain->elements[j] != NULL)
				{
					printf("%04d ", chain->hashKey);
					printf("%8s  %6d\n", chain->elements[j]->key, chain->elements[j]->value);
				}
			}
		}
	}
}

int main()
{
	printf("Hash table.\n");
	printf("Collision resolution: separate chaining with list head cells.\n\n");

	HashTable *table = newHashTable();
	add(table, "QWERTY", 1248);
	add(table, "QWERTY", 1250);
	add(table, "QWERTY", 1252);
	add(table, "QWERTY", 1248);
	add(table, "QWERTY", 1250);
	add(table, "QWERTY", 1252);
	add(table, "QWERTY", 1248);
	add(table, "QWERTY", 1250);
	add(table, "QWERTY", 1252);
	add(table, "QWERTY", 1248);
	add(table, "QWERTY", 1250);
	add(table, "QWERTY", 1252);
	add(table, "QWERTY", 1248);
	add(table, "QWERTY", 1250);
	add(table, "QWERTY", 1252);
	add(table, "WASD", 1254);
	add(table, "WASD", 1256);
	add(table, "ASDF", 1254);
	add(table, "ASDF", 1256);
	add(table, "ASDF", 1258);
	add(table, "ASDFWD", 1258);

	removeElement(table, "ASDFWD");

	printTable(table);

	return 0;
}