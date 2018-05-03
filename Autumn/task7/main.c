#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main()
{

    int sz;

    printf("%s", "Please, enter the size of the hash-table you want to create: ");
    scanf("%d", &sz);

    list **HTable = malloc(sz * sizeof(list*));

    build(sz, HTable);

    int input = -1;

    while (input != 0)
    {
        printf("%s",
               "Please, choose an option:\n1 - add an element\n2 - remove an element\n3 - search for an element\n4 - print the table\n0 - delete table\n");
        scanf("%d", &input);

        switch (input)
        {
            case 0:
                deleteTable(sz, HTable);
                break;
            case 1:
            {
                int key, value;
                printf("%s\n", "Enter the key and the value: ");
                scanf("%d %d", &key, &value);
                addElementWithKey(sz, HTable, key, value);
                break;
            }
            case 4:
            {
                output(sz, HTable);
                break;
            }
            case 2:
            {
                int key;
                printf("%s\n", "Enter the key of the element you want to delete: ");
                scanf("%d", &key);
                deleteElement(sz, HTable, key);
                break;
            }
            case 3:
            {
                int key;
                printf("%s\n", "Enter the key: ");
                scanf("%d", &key);
                findElement(sz, HTable, key);
            }

        }

    }

    free(HTable);

    return 0;
}
