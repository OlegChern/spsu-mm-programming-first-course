#include <stdio.h>

struct dynamicArray
{
    int arr[8];
    int size;
    struct dynamicArray *next;
};

struct dynamicArray createArr()
{
    struct dynamicArray arr;
    arr.size = 0;
    arr.next = NULL;

    return arr;
}

void addToEnd(struct dynamicArray *arr, int x)
{
    struct dynamicArray *newArr = arr;
    while (newArr->size == 8) newArr = newArr->next;

    newArr->arr[newArr->size] = x;
    newArr->size++;

    if (newArr->size == 8)
    {
        (*(newArr->next)).size = 0;
        for (int i = 0; i < 8; ++i)
        {
            (*(newArr->next)).arr[i] = i;
        }

        (*(newArr->next)).next = NULL;
    }
}


int at(struct dynamicArray *arr, int index)
{
    int value = 0;
    int ERR = 0;

    struct dynamicArray *newArr = arr;
    while (index >= 8)
    {
        index -= 8;

        if (newArr->size == 8) newArr = newArr->next;
        else
        {
            ERR = 1;
            break;
        }
    }
    if (!ERR)
    {
        if (newArr->size > index) value = newArr->arr[index];
        else ERR = 1;
    }


    if (ERR) printf("ERROR : Index out of bound!!!\n");
    return value;
}


int main()
{
    struct dynamicArray demo = createArr();

    addToEnd(&demo, 42);
    addToEnd(&demo, 17);
    addToEnd(&demo, 23);
    addToEnd(&demo, 5);
    addToEnd(&demo, 7);
    addToEnd(&demo, 2);
    addToEnd(&demo, 1);
    addToEnd(&demo, 7);

    addToEnd(&demo, 8);
    addToEnd(&demo, 2);
    addToEnd(&demo, 1);
    addToEnd(&demo, 2);
    addToEnd(&demo, 1);
    addToEnd(&demo, 19);

    for (int i = 6; i < 14; ++i)
    {
        printf("%d :: %d\n", i, at(&demo, i));
    }

    return 0;
}