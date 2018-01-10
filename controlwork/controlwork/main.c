#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct buff_list
{
	int key;
	int value;
	struct buff_list* next;
};

struct buffer
{
	struct buff_list* first;
	struct buff_list* last;
};

void buffInsert(struct buffer* buff, int key, int value)
{
	struct buff_list* temp = buff->last;

	if (temp->key == 0 && buff->last->value == 0)
	{
		temp->key = key;
		temp->value = value;
	}
	else
	{
		temp->next = malloc(sizeof(struct buff_list));
		temp = temp->next;

		temp->key = key;
		temp->value = value;
		temp->next = buff->first;

		buff->last = temp;
	}
}

int buffExtract(struct buffer* buff, int key)
{
	struct buff_list* temp = buff->first;
	struct buff_list* prvs = buff->last;

	if ((temp == prvs) && (temp->key == 0) && (temp->value == 0))
	{
		printf("error\n");
		return 0;
	}

	do
	{
		if (temp->key == key)
		{
			int res = temp->value;

			if (temp == buff->first)
			{
				buff->first = temp->next;
			}

			if (temp == buff->last)
			{
				buff->last = prvs;
			}

			prvs->next = temp->next;
			free(temp);

			return res;
		}

		prvs = temp;
		temp = temp->next;

	} while (temp != buff->first);

	printf("Not found\n");
	return 0;
}

int main()
{
	struct buff_list* list = malloc(sizeof(struct buff_list));
	list->value = 0;
	list->key = 0;
	list->next = list;

	struct buffer* buff = malloc(sizeof(struct buffer));
	buff->first = list;
	buff->last = list;

	buffExtract(buff, 2);

	buffInsert(buff, 1, 2);
	buffInsert(buff, 2, 4);
	buffInsert(buff, 3, 10);

	printf("%d\n", buffExtract(buff, 1));
	printf("%d\n", buffExtract(buff, 5));
	printf("%d\n", buffExtract(buff, 3));

	return 0;
	system("pause");
}
