// Память выделяется на 8 элементов
// Не успел сделать интерфейс
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ChunkDynamicArray
{
    int value;
    int depth;
    struct ChunkDynamicArray* next;
    bool mark;
};

struct ChunkDynamicArray* initialize(struct ChunkDynamicArray* NewStruct, int depth)
{
    NewStruct = malloc(sizeof(struct ChunkDynamicArray)*8);
    struct ChunkDynamicArray* test = NewStruct;

    for (int k = depth; k < depth+8; k++)
    {
        test->depth = k;
        test->value = 0;
        test->mark = false;
        if (k != depth+7) {
            test->next = test + 1;
            test = test->next;
        }
    }
    test->next = NULL;
    return NewStruct;
}


void addToEnd (int add_value, struct ChunkDynamicArray* test)
{
    while ((test->next != NULL) && (test->mark == true))
    {
        test = test->next;
    }
    if (test->mark == false)
    {
        test->value = add_value;
        test->mark = true;
    }
    else
    {
        test->next = initialize(test->next, test->depth + 1);
        test->next->value = add_value;
        test->next->mark = true;
    }

}

int at (int num, struct ChunkDynamicArray *test)
{
    while ((test->next != NULL) && (test->mark == true))
    {
        if (test->depth == num)
        {
            return test->value;
        }
        test = test->next;
    }
    return 0;
}

int main() {

    struct ChunkDynamicArray* NewStruct = initialize(NewStruct, 0);

    int a = 12;

    for (int i = 0; i < 8; i++)
    {
        addToEnd(a+i, NewStruct);
    }
    addToEnd(42, NewStruct);
    a = at(8, NewStruct);

    printf("%d", a);

    return 0;
}