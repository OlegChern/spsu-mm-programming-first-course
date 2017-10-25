#include <stdio.h>

typedef struct tagChDynArray
{
	//char *curRowStart; // start of this row
	int *current; // current element
	struct tagChDynArray* next;
} chDynArray;

void addToEnd(chDynArray*, int);
int at(chDynArray*, int);

int main()
{
	chDynArray *arr = (chDynArray*)malloc(sizeof(chDynArray));
	arr->current = arr;
	//arr->curRowIndex = 0;

	for (int j = 0; j < 10; j++)
	{
		addToEnd(arr, j);
	}

	for (int j = 0; j < 10; j++)
	{
		int a = at(arr, j);
		printf("%d\n", a);
	}
	int b = 0;
	scanf_s("%d", b);

	return 0;
}

void addToEnd(chDynArray *arr, int elem)
{
	// ñheck existing of chDynArray->next
	/*while (arr->next != NULL)
	{
		arr = arr->next;
	}*/

	if ((arr->current) - &arr > 3)
	{
		// create new row

		arr->next = (chDynArray*)malloc(sizeof(chDynArray));
		arr->next->current = arr->next;
		*(arr->next->current) = elem;
	}
	else
	{
		arr->current = arr->current + 1;
		*(arr->current) = elem;
	}
}

int at(chDynArray *arr, int index)
{
	int value;

	for (int i = 0; i < index / 4; i++)
	{
		if (arr->next != NULL)
		{
			arr = arr->next;
		}
		else
		{
			printf("Element with current index doesn't exist!");
			return 0;
		}
	}

	value = *(&arr + index % 4);

	return value;
}