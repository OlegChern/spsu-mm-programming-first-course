#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "header.h"

int main()
{
	hashTable* testHashTable = (hashTable*)malloc(sizeof(hashTable));

	initHashTable(testHashTable, 1);

	addKey("������", &testHashTable);             // ���������� �������� �� ������ � ��� �������
	addKey("�����", &testHashTable);
	addKey("����", &testHashTable);
	addKey("�����", &testHashTable);
	addKey("������2", &testHashTable);
	addKey("������3", &testHashTable);
	addKey("������4", &testHashTable);

	int k = 0;

	k = searchKey("����", testHashTable);     // ����� 1, �. �. ���� ����

	deleteKey("����", testHashTable);         // �������� �������� �� �����

	k = searchKey("����", testHashTable);     // ����� 0, �. �. ���� ���

	deleteHashTable(testHashTable);           // �������� ��� �������

	_getch();

	return 0;
}