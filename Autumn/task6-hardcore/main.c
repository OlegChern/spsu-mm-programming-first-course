#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"
#include "fileIO.h"

int mstrcmp(const void *a, const void *b)
{
    char *astr = *(char **) a;
    char *bstr = *(char **) b;
    return strcmp(astr, bstr);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 1;
    }

    clock_t start = clock();

    HashTable *table = buildHashTable();

    if (fillTable(table, argv[1]))
        return 1;

    StringArray *array = getKeys(table);

    qsort(array->data, array->length, sizeof(char *), &mstrcmp);

    if (saveText(table, array, argv[0]))
        return 1;

    freeStringArray(array);
    freeHashTable(table);

    clock_t end = clock();
    printf("\nDone, %.02f sec\n", (double) (end - start) / CLOCKS_PER_SEC);

    return 0;
}
