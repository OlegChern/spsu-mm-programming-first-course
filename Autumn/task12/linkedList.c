#include <stdio.h>
#include <malloc.h>

#include "linkedList.h"

/* ==== ==== implementation-dependent ==== ==== */

int equal(LIST_VALUE_TYPE first, LIST_VALUE_TYPE second)
{
    return first == second;
}

void printListElement(LIST_VALUE_TYPE value)
{
    printf("%d", value);
}

/* ==== ==== implementation-independent ==== ==== */

Element *buildElement(LIST_VALUE_TYPE value)
{
    Element *result = malloc(sizeof(Element));
    result->value = value;
    result->next = NULL;
    return result;
}

LinkedList *buildLinkedList()
{
    LinkedList *result = malloc(sizeof(LinkedList));
    result->first = NULL;
    result->length = 0;
    return result;
}

void addToList(LinkedList *list, LIST_VALUE_TYPE value)
{
    if (list == NULL)
        return;
    Element *newElement = buildElement(value);
    if (list->first == NULL)
    {
        list->first = newElement;
        list->length = 1;
        return;
    }
    Element *current = list->first;
    while (current->next != NULL)
        current = current->next;
    current->next = newElement;
    list->length++;
}

void removeValueFromList(LinkedList *list, LIST_VALUE_TYPE value)
{
    if (list == NULL || list->first == NULL)
        return;
    if (equal(list->first->value, value))
    {
        Element *tmp = list->first;
        list->first = list->first->next;
        list->length--;
        free(tmp);
        return;
    }
    Element *current = list->first;
    while (current->next != NULL)
    {
        if (equal(current->next->value, value))
        {
            removeNext(list, current);
            return;
        }
        current = current->next;
    }
}

void removeNext(LinkedList *list, Element *element)
{
    if (element->next == NULL)
        return;
    Element *tmp = element->next;
    element->next = tmp->next;
    list->length--;
    free(tmp);
}

void printList(LinkedList *list)
{
    if (list == NULL)
    {
        printf("NULL");
        return;
    }
    printf("[");
    Element *current = list->first;
    while (current != NULL)
    {
        printListElement(current->value);
        if (current->next != NULL)
            printf(", ");
        current = current->next;
    }
    printf("]");
}

void freeList(LinkedList *list)
{
    if (list == NULL)
        return;
    freeListContents(list);
    free(list);
}

void freeListContents(LinkedList *list)
{
    if (list == NULL)
        return;
    Element *current = list->first;
    while (current != NULL)
    {
        Element *tmp = current;
        current = current->next;
        free(tmp);
    }
}
