#include<stdio.h>
#include<stdlib.h>
#include "hash.h"

list* create ( int _key, int data )
{
    list* tmp = (list*)malloc(sizeof(list));
    tmp -> value = data;
    tmp -> key = _key;
    tmp -> next = NULL;
    return(tmp);
}

void addToEnd( int _key, int data, list* head)
{
    list *tmp = (list*)malloc(sizeof(list));
    tmp -> value = data;
    tmp -> key = _key;
    tmp -> next = NULL;
    list *p = head;
    while (p -> next != NULL)
        p = p -> next;
    p -> next = tmp;
}

list *lookUp (int _key, list* head)
{
    if (head == NULL) {
        return NULL;
    }
    if (head -> key == _key) {
        return head;
    } else {
        return lookUp ( _key, head->next );
    }
}

list *removeElement(int _key, list *head)
{
    list *tmp = head;
    list *p = NULL;
    if (head == NULL)
        return NULL;
    while ( (tmp) && (tmp -> key != _key))
    {
        p = tmp;
        tmp = tmp -> next;
    }
    if (tmp == head)
    {
        free(head);
        return tmp -> next;
    }
    if (!tmp)
        return head;
    p -> next = tmp -> next;
    free(tmp);
    return head;
}

list *deleteList(list *head)
{
    while (head != NULL)
    {
        list *p = head;
        head = head -> next;
        free(p);
    }
    return NULL;
}

void printList( list *head)
{
    if (head)
    {
        printf( "the key is %d\nthe value is %d\n", head->key, head->value);
        printList(head->next);
    }
}

void build (int size, list** table)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        table[i] = NULL;
    }
}

void output (int size, list** table)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        printList(table[i]);
    }
}

void addElementWithKey (int size, list** table, int _key, int _data)
{
    if ( table[_key % size] )
    {
        addToEnd( _key, _data, table[_key % size] );
    } else
    {
        table[_key % size] = create( _key, _data);
    }
}

void deleteElement (int size, list** table, int _key)
{
    int index = _key % size;
    table[index] = removeElement(_key, table[index]);
}

void findElement(int size, list** table, int _key)
{
    int index = _key % size;
    int WasNotFound = 1;
    list* tmp = table[index];
    while (tmp)
    {
        if (tmp->key == _key)
        {
            if (WasNotFound)
            {
                WasNotFound = 0;
                printf("Founded values:\n");
            }
            printf("%d ", tmp->value);

        }
        tmp = tmp->next;
    }
    if (WasNotFound)
    {
        printf("%s", "There is no match for this key");
    }
    printf("\n");
}

void deleteTable(int size, list** table)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        deleteList(table[i]);
    }
}
