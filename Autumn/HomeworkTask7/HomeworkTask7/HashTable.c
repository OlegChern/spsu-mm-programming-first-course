#include <stdio.h>
#include "HashTable.h"

// add new key and value
void add(HashTable *table, char* key, int value)
{
	HashTableChain *chain = findChain(table, hash(table, key));

	if (chain == NULL) // wasn't found
	{
		chain = addEmptyChain(table);
	}

	HashTableElement *element = addEmptyElement(chain);
	element->value = value;
	element->key = key;

	// rebalance
	if (chain->elementCount > BINSIZE)
	{
		rebalance(table);
	}
}

// find value with given key, returns NULL if key wasn't found
int *findValue(HashTable *table, char* key)
{
	HashTableChain *chain = findChain(table, hash(table, key));
	HashTableElement *element = findElement(chain, key);
	if (element != NULL) // was found
	{
		return element->value;
	}

	return NULL;
}

// remove key and value
void removeElement(HashTable *table, char* key)
{
	HashTableChain *chain = findChain(table, hash(table, key));
	HashTableElement *element = findElement(chain, key);
	if (element != NULL) // was found
	{
		
	}
}

void printTable(HashTable* table)
{
	for (int i = 0; i < table->chainCount; i++)
	{
		printf("\n");

		HashTableChain *chain = table->chains[i];

		for (int j = 0; j < chain->elementCount; j++)
		{
			printf("%010d ", chain->hashKey);
			printf("%12s  %010d\n", chain->elements[j]->key, chain->elements[j]->value);
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
	add(table, "WASD", 1254);
	add(table, "WASD", 1256);
	add(table, "ASDF", 1254);
	add(table, "ASDF", 1256);
	add(table, "ASDF", 1258);

	printTable(table);

	return 0;
}