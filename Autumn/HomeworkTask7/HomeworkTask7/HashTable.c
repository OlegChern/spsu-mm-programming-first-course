#include <stdio.h>
#include "HashTable.h"

// add new key and value
void add(HashTable *table, char* key, int value)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	if (chain->elementCount + 1 >= MAXCHAINSIZE)
	{
		rebalance(table);
		chain = table->chains[hash(table, key)]; // calculate hash with new table
	}

	HashTableElement *element = (HashTableElement*)malloc(sizeof(HashTableElement));
	element->value = value;
	element->key = key;

	chain->elements[chain->elementCount++] = element;

}

// find pointer to value with given key, returns 0 if key wasn't found
int findValue(int *buffer, HashTable *table, char* key)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	HashTableElement *element = findElement(chain, key);
	if (element != NULL)
	{
		*buffer = element->value;
		return 1;
	}

	buffer = NULL;
	return 0;
}

// remove key and value
void removeElement(HashTable *table, char* key)
{
	HashTableChain *chain = table->chains[hash(table, key)];

	int index = findElementIndex(chain, key);
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

int main()
{
	printf("Hash table.\n");
	printf("Collision resolution: separate chaining with list head cells.\n");

	HashTable *table = newHashTable();
	add(table, "WADX", 1248);
	add(table, "EDSF", 1250);
	add(table, "ZXC", 1252);
	add(table, "ASDX", 1248);
	add(table, "ZXCV", 1250);
	add(table, "WASD", 1254);
	add(table, "WASD", 1256);
	add(table, "ASDF", 1254);
	add(table, "ZXCV", 1256);
	add(table, "ASDFDS", 1258);
	add(table, "ASDFWD", 1258);

	printTable(table);

	printf("Removing elements with keys \"ASDFDS\" and \"ASDFWD\"\n");

	removeElement(table, "ASDFDS");
	removeElement(table, "ASDFWD");

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