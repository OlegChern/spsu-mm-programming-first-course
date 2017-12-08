#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* ==== ==== implementation-dependent ==== ==== */

#ifndef LIST_VALUE_TYPE
#define LIST_VALUE_TYPE unsigned int
#endif

int equal(LIST_VALUE_TYPE, LIST_VALUE_TYPE);

void printListElement(LIST_VALUE_TYPE, char *);

/* ==== ==== implementation-independent ==== ==== */

typedef struct Element
{
    LIST_VALUE_TYPE value;
    struct Element *next;
    struct Element *previous;
} Element;

typedef struct
{
    Element *first;
    unsigned int length;
    Element *last;
} LinkedList;

Element *buildElement(LIST_VALUE_TYPE);

LinkedList *buildLinkedList();

int listIsValid(LinkedList *list);

void addElementToList(LinkedList *, Element *);

void addValueToList(LinkedList *, LIST_VALUE_TYPE);

void addAllValuesToList(LinkedList *, int, ...);

/// Removes first occurance
void removeValueFromList(LinkedList *, LIST_VALUE_TYPE);

void removeFromList(LinkedList *, Element *);

Element *popFirst(LinkedList *);

Element *popLast(LinkedList *);

void printList(LinkedList *, char *);

/// Frees the pointer
void freeList(LinkedList *);

/// Leaves the pointer
void freeListContents(LinkedList *);

#endif /* LINKEDLIST_H */
