#include <stdlib.h>
#include <string.h>
#include "Header.h"

NODE **getNode(HASHTABLE *, char*);
int hash(char*);
void recalc(HASHTABLE *);

HASHTABLE *create()
{
	HASHTABLE *ht = malloc(sizeof(HASHTABLE));
	if (ht == 0)
	{
		return 0;
	}
	ht->size = 0;
	ht->capacity = INITIAL_CAPACITY;
	ht->table = calloc(INITIAL_CAPACITY, sizeof(NODE*));
	if (ht->table == 0)
	{
		return 0;
	}
	return ht;
}

void *get(HASHTABLE *ht, char *key)
{
	NODE **node = getNode(ht, key);
	return node ? (*node)->value : 0;
}

void put(HASHTABLE *ht, char *key, void *value)
{
	NODE **node = getNode(ht, key);
	if (node)
	{
		(*node)->value = value;
	}
	else
	{
		int h = hash(key) & (ht->capacity - 1);
		NODE *newNode = malloc(sizeof(NODE));
		newNode->key = key;
		newNode->value = value;
		newNode->next = ht->table[h];
		ht->table[h] = newNode;
		ht->size++;
		if (ht->size / (double)(ht->capacity) > RECALC)
		{
			recalc(ht);
		}
	}
}

void delete(HASHTABLE *ht, char *key)
{
	NODE **node = getNode(ht, key);
	if (node)
	{
		NODE *oldNode = *node;
		*node = oldNode->next;
		free(oldNode);
	}
}

int hash(char *key)
{
	int s = 0;
	while (*key)
	{
		s *= 19;
		s += *key++;
	}
	return s;
}

NODE **getNode(HASHTABLE *ht, char *key)
{
	int h = hash(key) & (ht->capacity - 1);
	NODE **node = ht->table + h;
	while (*node && strcmp(key, (*node)->key) != 0)
	{
		node = &((*node)->next);
	}
	return *node ? node : 0;
}

void recalc(HASHTABLE * ht)
{
	int i;
	if (ht->capacity == MAX_CAPACITY) return;
	NODE **oldTable = ht->table;
	ht->table = calloc(ht->capacity <<= 1, sizeof(NODE*));
	ht->size = 0;
	for (i = 0; i < (ht->capacity >> 1); i++)
	{
		NODE *node = oldTable[i];
		while (node)
		{
			NODE *oldNode = node;
			node = node->next;
			put(ht, oldNode->key, oldNode->value);
			free(oldNode);
		}
	}
}



