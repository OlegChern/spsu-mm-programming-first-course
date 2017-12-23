#include "stdio.h"
#include "stdlib.h"
#include "header.h"

const int maxLengthList = 3;               // ����� ������� ������ ������� (���� ����� 3, �� ���������������)

void initHashTable(hashTable* hashTable, int size)            // �������� ������ ��� �������
{
	hashTable->size = size;
	hashTable->lists = (list*)malloc(sizeof(list) * size);
	for (int i = 0; i < size; i++)
	{
		hashTable->lists[i].length = 0;
		hashTable->lists[i].head = NULL;
	}
}

int hashFunction(const char* string, int size)              // ��� ������� �� ����� � ��������
{
	unsigned int hash = 0;

	while (*string != 0)
	{
		hash = (hash * 1664525) + (unsigned char)(*string) + 1013904223;
		string++;
	}
	hash %= size;

	return hash;
}

void addKey(const char* string, hashTable** hashTable)         // ���������� �������� �� �����
{
	int value = hashFunction(string, (*hashTable)->size);

	addValue(&((((*hashTable)->lists)[value]).head), string);
	(((*hashTable)->lists)[value]).length++;
	if ((*hashTable)->lists[value].length == maxLengthList)         // �������� ����� ������ �� ���������� ��������
	{
		*hashTable = rehash(*hashTable);                     // ���������� ������ ��������� �� ������������������� �������
	}
}

hashTable* rehash(hashTable* oldHashTable)                           //���������������
{
	hashTable* newHashTable = (hashTable*)malloc(sizeof(hashTable));            
	initHashTable(newHashTable, oldHashTable->size * 2);                     //�������� ����� ��� ������� � ���������� � 2 ���� ������ ������
	for (int i = 0; i < oldHashTable->size; i++)
	{
		
		for (int j = 0; j < oldHashTable->lists[i].length; j++)              //������� ��������� ������� � �����, � �� �������� � ������
		{
			const char* string = oldHashTable->lists[i].head->string;
			deleteValue(&(oldHashTable->lists[i].head), string); 
			addKey(string, &newHashTable);
		}
	}
	free(oldHashTable->lists);           //������� ������ ������ ��� �������
	free(oldHashTable);                  //
	return newHashTable;
}

void deleteKey(const char* string, hashTable* hashTable)           // �������� �������� �� �����
{
	int hash = hashFunction(string, hashTable->size);
	deleteValue(&(hashTable->lists[hash].head), string);
}

int searchKey(const char* string, hashTable* hashTable)            // ���������� 1 ���� �������� �� ������� ����� �������, ����� 0
{
	int hash = hashFunction(string, hashTable->size);
	return isBelong(&(hashTable->lists[hash].head), string);
}

void deleteHashTable(hashTable* hashTable)                       // �������� ��� �������
{
	for (int i = 0; i < hashTable->size; i++)
	{
		deleteList(&(hashTable->lists[i].head));
	}
	free(hashTable->lists);
	free(hashTable);
}