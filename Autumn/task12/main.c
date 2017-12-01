#include <stdio.h>
#include "linkedList.h"

int main()
{
    LinkedList *list = buildLinkedList();
    addToList(list, 12);
    addToList(list, 13);
    removeNext(list, list->first);
    printList(list);
    freeList(list);
    return 0;
}