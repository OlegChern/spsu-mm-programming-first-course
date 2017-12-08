#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>

#include "linkedList.h"

/* ==== ==== implementation-dependent ==== ==== */

int equal(LIST_VALUE_TYPE first, LIST_VALUE_TYPE second)
{
    return first == second;
}

void printListElement(LIST_VALUE_TYPE value, char *format)
{
    printf(format, value);
}

/* ==== ==== implementation-independent ==== ==== */

Element *buildElement(LIST_VALUE_TYPE value)
{
    Element *result = malloc(sizeof(Element));
    result->value = value;
    result->next = NULL;
    result->previous = NULL;
    return result;
}

LinkedList *buildLinkedList()
{
    LinkedList *result = malloc(sizeof(LinkedList));
    result->first = NULL;
    result->last = NULL;
    result->length = 0;
    return result;
}

int listIsValid(LinkedList *list)
{
    // Check that values stored in list
    // do not contradict each other.
    // It is unclear whether it is possible
    // to simplify this condition or not.
    return list != NULL
           && (list->first == NULL && list->last == NULL && list->length == 0
               || list->first != NULL && list->last != NULL && list->length != 0
           );
}

// Intentianally hidden from outer scope
// by not being included into linkedList.h
void unsafeAddElementToList(LinkedList *list, Element *element)
{
    if (list->length == 0)
    {
        list->first = element;
        list->last = element;
        list->length = 1;
        return;
    }
    list->last->next = element;
    element->previous = list->last;
    list->length++;
    list->last = element;
}

void addElementToList(LinkedList *list, Element *element)
{
    if (!listIsValid(list))
    {
        printf("Error: linked list is likely corrupted.");
        return;
    }
    unsafeAddElementToList(list, element);
}

void addValueToList(LinkedList *list, LIST_VALUE_TYPE value)
{
    if (!listIsValid(list))
    {
        printf("Error: linked list is likely corrupted.");
        return;
    }
    Element *newElement = buildElement(value);
    unsafeAddElementToList(list, newElement);
}

void addAllValuesToList(LinkedList *list, int count, ...)
{
    va_list arg_list;
    va_start(arg_list, count);
    for (int i = 0; i < count; i++)
    {
        LIST_VALUE_TYPE arg = va_arg(arg_list, LIST_VALUE_TYPE);
        addValueToList(list, arg);
    }
}

void removeValueFromList(LinkedList *list, LIST_VALUE_TYPE value)
{
    if (list == NULL || list->first == NULL)
        return;
    if (equal(list->first->value, value))
    {
        Element *tmp = list->first;
        list->first = list->first->next;
        if (list->first != NULL)
            list->first->previous = NULL;
        list->length--;
        if (list->last == tmp)
            list->last = NULL;
        free(tmp);
        return;
    }
    Element *current = list->first;
    while (current->next != NULL)
    {
        if (equal(current->next->value, value))
        {
            removeFromList(list, current);
            return;
        }
        current = current->next;
    }
}

void removeFromList(LinkedList *list, Element *element)
{
    if (element == NULL)
        return;

    if (element->next != NULL)
        element->next->previous = element->previous;

    if (element->previous != NULL)
        element->previous->next = element->next;

    list->length--;

    if (list->first == element)
        list->first = element->next;

    if (list->last == element)
        list->last = element->previous;

    free(element);
}

Element *popFirst(LinkedList *list)
{
    if (list == NULL || list->length == 0)
        return NULL;

    Element *first = list->first;
    list->length--;

    if (list->length == 0)
    {
        list->first = NULL;
        list->last = NULL;
        return first;
    }

    first->next->previous = NULL;
    list->first = first->next;
    first->next = NULL;
    return first;
}

Element *popLast(LinkedList *list)
{
    if (list == NULL || list->length == 0)
        return NULL;

    Element *last = list->last;
    list->length--;

    if (list->length == 0)
    {
        list->last = NULL;
        list->first = NULL;
        return last;
    }

    last->previous->next = NULL;
    list->last = last->previous;
    last->previous = NULL;
    return last;
}

void printList(LinkedList *list, char *format)
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
        printListElement(current->value, format);
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
