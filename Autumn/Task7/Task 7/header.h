#pragma once

struct listElement                // Структура элемента списка: строка и указатель на следующий элемент
{
	const char* string;
	struct listElement* pointerNext;
};

typedef struct listElement listElement;

typedef struct            // Структура списка: еог длина и указатель на первый элемент
{
	int length;
	listElement* head;
}list;

typedef struct             // Структура хэш таблицы: размер и указатель на массив списков
{
	int size;
	list* lists;
}hashTable;

void addValue(listElement** head, const char* string);

int deleteValue(listElement** head, const char* string);

int isBelong(listElement** head, const char* string);

void deleteList(listElement** head);

void initHashTable(hashTable* hashTable, int size);

int hashFunction(const char* string, int size);

void addKey(const char* string, hashTable** hashTable);

hashTable* rehash(hashTable* oldHashTable);

void deleteKey(const char* string, hashTable* hashTable);

int searchKey(const char* string, hashTable* hashTable);

void deleteHashTable(hashTable* hashTable);