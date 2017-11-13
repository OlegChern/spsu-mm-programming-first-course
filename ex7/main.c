#include "header.h"

struct list
{
    int value;
    int key;
    struct list* next;
};


struct hash_t
{
    struct list* arr_lst;
    int size;
    int counter;
};


int main() {

    int sz;

    printf("%s", "Please, enter the size of the hash-table you want to create: ");
    scanf("%d", &sz);

    struct hash_t* table;

    table->size = sz;
    table->counter = 0;
    table->arr_lst = malloc(sizeof(struct list)*sz);

    int input = -1;

    while (input != 0)
    {
        printf("%s", "Please, choose an option: 1 - add an element, 2 - remove an element, 3 - search for an element, 4 - print the table, 0 - delete the table\n");
        scanf("%d", &input);

        switch(input) {
            case 0:
                hash_Delete(table);
                break;
            case 1: {
                int key, value;
                printf("%s\n", "Enter the key and the value: ");
                scanf("%d %d", &key, &value);
                hash_Add(table, key, value);
                break;
            }
            case 4: {
                hash_Print(table);
                break;
            }
            case 2: {
                int key;
                scanf("%d", &key);
                hash_Remove(table, key);
                break;
            }
            case 3:
            {
                int key, value;
                printf("%s\n", "Enter the key: ");
                scanf("%d", &key);
                if(hash_Search(table,key,&value))
                {
                    printf("%s%d\n","The value is ", value);
                }
                else
                {
                    printf("%s", "There is no match for this key\n");
                }
            }

        }

    }

    return 0;
}

void list_AddToEnd (int add_value, int add_key, struct list* list)
{
    struct list* l = list;

    while (l->next != NULL)
    {
        if (l->key == add_key)
        {
            l->value = add_value;
            return;
        }
        l = l->next;
    }

    l->key = add_key;
    l->value = add_value;
    l->next = malloc(sizeof(struct list));

    l->next->value = 0;
    l->next->key = 0;
    l->next->next = NULL;
}

void list_ValueRemove (int remove_key, struct list* l)
{
    if (l->key == remove_key)
    {
        l->key = l->next->key;
        l->value = l->next->value;
        struct list* temp = l->next;
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
        struct list* temp;
        temp = l->next->next;
        free(l->next);
        l->next = temp;
    }
}

bool list_Search (int search_key, struct list* l, int *num)
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

void list_Print (struct list* l)
{
    while(l->next != NULL)
    {
        printf("(%d , %d) ", l->key, l->value);
        l = l->next;
    }
}

void list_Delete(struct list* list)
{
    if (list == NULL) return;

    list_Delete(list->next);
    free(list);

}


int hash_func (int key, struct hash_t* table)
{
    return key % table->size;
}

void hash_Resize(struct hash_t* table)
{
    struct list* new_lists = malloc(sizeof(struct list)*table->size);
    for (int i = 0; i < table->size; i++)
    {
        struct list* l = table->arr_lst + i;
        while (l->next != NULL)
        {
            list_AddToEnd(l->value, l->key, new_lists + hash_func(l->key, table));
            l = l->next;
        }
    }

    hash_Delete(table);
    table->size *= 2;
    table->arr_lst = malloc(sizeof(struct list)*table->size);

    for (int j = 0; j < table->size / 2; j++)
    {
        struct list* l = new_lists + j;
        while (l->next != NULL)
        {
            list_AddToEnd(l->value, l->key, table->arr_lst + hash_func(l->key, table));
            l = l->next;
        }
    }


    printf("%s", "The table has been resized (size is doubled)\n");
}

void hash_Add (struct hash_t* table, int key, int value)
{
    struct list* list = (table->arr_lst + hash_func(key,table));

    table->counter++;
    list_AddToEnd(value, key, list);

    if (table->counter == table->size + 2)
    {
        hash_Resize(table);
    }
}

bool hash_Search (struct hash_t* table, int key, int* num)
{
    struct list *list = table->arr_lst + hash_func(key, table);

    if (list_Search(key, list, num))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void hash_Remove (struct hash_t* table, int key)
{
    struct list* list = table->arr_lst + hash_func(key,table);

    table->counter--;
    while (list != NULL)
    {
        if (list->key == key)
        {
            list_ValueRemove(key, list);
            return;
        }
        list = list->next;
    }
}

void hash_Print (struct hash_t* table)
{
    for (int i = 0; i < table->size; i++)
    {
        list_Print(table->arr_lst + i);
        printf("\n");
    }
}

void hash_Delete(struct hash_t* table)
{
    for (int i = 0; i < table->size; i++)
    {
        list_Delete((table->arr_lst + i)->next);
    }
    table->counter = 0;
    free(table->arr_lst);
}


