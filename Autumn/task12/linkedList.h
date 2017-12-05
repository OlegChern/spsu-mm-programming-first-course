#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* ==== ==== implementation-dependent ==== ==== */

#ifndef LIST_VALUE_TYPE
#define LIST_VALUE_TYPE unsigned int
#endif

int equal(LIST_VALUE_TYPE, LIST_VALUE_TYPE);

void printListElement(LIST_VALUE_TYPE);

/* ==== ==== implementation-independent ==== ==== */

typedef struct Element
{
    LIST_VALUE_TYPE value;
    struct Element *next;
} Element;

typedef struct
{
    Element *first;
    int length;
    Element *last;
} LinkedList;

Element *buildElement(LIST_VALUE_TYPE);

LinkedList *buildLinkedList();

void addToList(LinkedList *, LIST_VALUE_TYPE);

void addAllToList(LinkedList *, int, ...);

/// Removes first occurance
void removeValueFromList(LinkedList *, LIST_VALUE_TYPE);

void removeNext(LinkedList *, Element *);

void printList(LinkedList *);

/// Frees the pointer
void freeList(LinkedList *);

/// Leaves the pointer
void freeListContents(LinkedList *);

#endif /* LINKEDLIST_H */
