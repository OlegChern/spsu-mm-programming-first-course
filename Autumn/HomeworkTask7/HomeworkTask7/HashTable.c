#include <stdio.h>
#include "HashTable.h"

int main()
{
	printf("Hash table.\n");
	printf("Collision resolution: separate chaining with list head cells.\n");

	HashTable *table = newHashTable();
	addKey(table, "WADX", 1248);
	addKey(table, "EDSF", 1250);
	addKey(table, "ZXC", 1252);
	addKey(table, "ASDX", 1248);
	addKey(table, "ZXCV", 1250);
	addKey(table, "WASD", 1254);
	addKey(table, "WASD", 1256);
	addKey(table, "ASDF", 1254);
	addKey(table, "ZXCV", 1256);
	addKey(table, "ASDFDS", 1258);
	addKey(table, "ASDFWD", 1258);

	printTable(table);

	printf("Removing elements with keys \"ASDFDS\" and \"ASDFWD\"\n");

	removeKey(table, "ASDFDS");
	removeKey(table, "ASDFWD");

	printTable(table);

	int buffer;
	char key[2][5] = { "ZXCV", "TEST" };

	for (int i = 0; i < 2; i++)
	{
		if (findValue(&buffer, table, key[i]))
		{
			printf("Value of element with key \"%s\": %d\n", key[i], buffer);
		}
		else
		{
			printf("Value of element with key \"%s\" not found\n", key[i]);
		}
	}

	return 0;
}


// add new key and value
void addKey(HashTable *table, char* key, int value)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	HashTableElement *element = (HashTableElement*)malloc(sizeof(HashTableElement));
	element->value = value;
	element->key = key;

	// first add
	chain->elements[chain->elementCount] = element;
	chain->elementCount++;

	// then check
	if (chain->elementCount >= MAXCHAINSIZE)
	{
		rebalance(table);
	}
}

// find pointer to value with given key, returns 0 if key wasn't found
int findValue(int *buffer, HashTable *table, char* key)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	HashTableElement *element = findElementInChain(chain, key);
	if (element != NULL)
	{
		*buffer = element->value;
		return 1;
	}

	buffer = NULL;
	return 0;
}

// remove key and value
void removeKey(HashTable *table, char* key)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	int index = findElementIndexInChain(chain, key);
	if (index >= 0) // was found
	{
		for (int i = index; i < chain->elementCount - 1; i++)
		{
			chain->elements[i] = chain->elements[i + 1];
		}

		free(chain->elements[chain->elementCount--]);
	}
}

void printTable(HashTable* table)
{
	printf("\nHash table: [hash key] [key] [value]");

	for (int i = 0; i < table->chainCount; i++)
	{
		HashTableChain *chain = table->chains[i];

		if (chain->elementCount > 0)
		{
			printf("\n");
			
			for (int j = 0; j < chain->elementCount; j++)
			{
				HashTableElement *element = chain->elements[j];

				if (element != NULL)
				{
					printf("%04d ", hash(table, element->key));
					printf("%8s  %6d\n", element->key, element->value);
				}
			}
		}
	}

	printf("\n");
}

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
		table->chains[i] = createEmptyChain();
	}

	return table;
}

HashTableChain *createEmptyChain()
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

HashTableElement *findElementInChain(HashTableChain *chain, char* key)
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

int findElementIndexInChain(HashTableChain *chain, char* key)
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

	// creating temp array of pointers for changing indices
	HashTableChain **temp = (HashTableChain**)malloc(sizeof(HashTableChain*) * table->chainCount);
	for (int i = 0; i < table->chainCount; i++)
	{
		temp[i] = createEmptyChain();
	}

	for (int i = 0; i < prevCount; i++)
	{
		HashTableChain *sourceChain = table->chains[i];

		for (int j = 0; j < sourceChain->elementCount; j++)
		{
			int hashKey = hash(table, sourceChain->elements[j]->key);
			temp[hashKey]->elements[temp[hashKey]->elementCount] = sourceChain->elements[j];
			temp[hashKey]->elementCount++;
		}

		// free table->chains[i] because they will be replaced by temp[i]
		free(sourceChain);
	}

	for (int i = 0; i < table->chainCount; i++)
	{
		table->chains[i] = temp[i];
	}

	// free only array of pointers but not themselves
	free(temp);
}