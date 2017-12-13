#include "header.h"

struct list
{
    int value;
    int key;
    struct list *next;
};


struct hash_t
{
    struct list *arr_lst;
    int size;
};


int main()
{

    int sz;

    printf("%s", "Please, enter the size of the hash-table you want to create: ");
    scanf("%d", &sz);

    struct hash_t *table = malloc(sizeof(struct hash_t));

    initialize(sz, table);

    int input = -1;

    while (input != 0)
    {
        printf("%s",
               "Please, choose an option: 1 - add an element, 2 - remove an element, 3 - search for an element, 4 - print the table, 0 - delete the table\n");
        scanf("%d", &input);

        switch (input)
        {
            case 0:
                hashDelete(table);
                break;
            case 1:
            {
                int key, value;
                printf("%s\n", "Enter the key and the value: ");
                scanf("%d %d", &key, &value);
                hashAdd(table, key, value);
                break;
            }
            case 4:
            {
                hashPrint(table);
                break;
            }
            case 2:
            {
                int key;
                printf("%s\n", "Enter the key of the element you want to delete: ");
                scanf("%d", &key);
                hashRemove(table, key);
                break;
            }
            case 3:
            {
                int key, value;
                printf("%s\n", "Enter the key: ");
                scanf("%d", &key);
                if (hashSearch(table, key, &value))
                {
                    printf("%s%d\n", "The value is ", value);
                } else
                {
                    printf("%s", "There is no match for this key\n");
                }
            }

        }

    }

    free(table);

    return 0;
}

struct hash_t* initialize(int size, struct hash_t* table)
{
    table->size = size;
    table->arr_lst = malloc(sizeof(struct list) * size);

    for (int i = 0; i < size; i++)
    {
        table->arr_lst[i].next = NULL;
        table->arr_lst[i].value = 0;
        table->arr_lst[i].key = 0;
    }
}

int listAddToEnd(int add_value, int add_key, struct list *list)
{
    int counter = 0;

    struct list *l = list;

    while (l->next != NULL)
    {
        if (l->key == add_key)
        {
            l->value = add_value;
            return 0;
        }
        counter++;
        l = l->next;
    }

    l->key = add_key;
    l->value = add_value;
    l->next = malloc(sizeof(struct list));

    l->next->value = 0;
    l->next->key = 0;
    l->next->next = NULL;

    return counter + 1;
}

void listValueRemove(int remove_key, struct list *l)
{
    if (l->key == remove_key)
    {
        l->key = l->next->key;
        l->value = l->next->value;
        struct list *temp = l->next;
        l->next = l->next->next;
        free(temp);
        return;
    }

    while ((l->next != NULL) && (l->next->key != remove_key))
    {
        l = l->next;
    }

    if (l->next->key == remove_key)
    {
        struct list *temp;
        temp = l->next->next;
        free(l->next);
        l->next = temp;
    }
}

bool listSearch(int search_key, struct list *l, int *num)
{
    while (l->next != NULL)
    {
        if (l->key == search_key)
        {
            *num = l->value;
            return true;
        }
        l = l->next;
    }
    return false;
}

void listPrint(struct list *l)
{
    while (l->next != NULL)
    {
        printf("(%d , %d) ", l->key, l->value);
        l = l->next;
    }
}

void listDelete(struct list *list)
{
    if (list == NULL) return;

    listDelete(list->next);
    free(list);

}


int hashFunc(int key, struct hash_t *table)
{
    return key % table->size;
}

void hashResize(struct hash_t *table)
{
    int new_size = table->size*2;

    struct list *new_lists = malloc(sizeof(struct list) * table->size);
    for (int i = 0; i < table->size; i++)
    {
        struct list *l = table->arr_lst + i;
        while (l->next != NULL)
        {
            listAddToEnd(l->value, l->key, new_lists + hashFunc(l->key, table));
            l = l->next;
        }
    }

    hashDelete(table);

    initialize(new_size, table);

    for (int j = 0; j < table->size / 2; j++)
    {
        struct list *l = new_lists + j;
        while (l->next != NULL)
        {
            listAddToEnd(l->value, l->key, table->arr_lst + hashFunc(l->key, table));
            l = l->next;
        }
    }


    printf("%s", "The table has been resized (size is doubled)\n");
}

void hashAdd(struct hash_t *table, int key, int value)
{
    struct list *list = (table->arr_lst + hashFunc(key, table));

    int counter;

    counter = listAddToEnd(value, key, list);

    if (counter == (table->size + 2) / 2)
    {
        hashResize(table);
    }
}

bool hashSearch(struct hash_t *table, int key, int *num)
{
    struct list *list = table->arr_lst + hashFunc(key, table);

    if (listSearch(key, list, num))
    {
        return true;
    } else
    {
        return false;
    }
}

void hashRemove(struct hash_t *table, int key)
{
    struct list *list = table->arr_lst + hashFunc(key, table);

    while (list != NULL)
    {
        if (list->key == key)
        {
            listValueRemove(key, list);
            printf("%s\n", "Element has been deleted");
            return;
        }
        list = list->next;
    }
    printf("%s\n", "Element has not been found");
}

void hashPrint(struct hash_t *table)
{
    for (int i = 0; i < table->size; i++)
    {
        listPrint(table->arr_lst + i);
        printf("\n");
    }
}

void hashDelete(struct hash_t *table)
{
    for (int i = 0; i < table->size; i++)
    {
        listDelete((table->arr_lst + i)->next);
    }
    free(table->arr_lst);
}


