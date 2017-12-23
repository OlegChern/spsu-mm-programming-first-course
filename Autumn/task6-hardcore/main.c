#include <stdio.h>
#include <time.h>
#include <mem.h>
// #include <stdlib.h>

#include "hashTable.h"
#include "fileIO.h"

int getStringLengthDelta1(const char *buf, unsigned int length)
{
    unsigned int result = 0;
    while (1)
    {
        if (result >= length || buf[result] == '\n')
            return result;
        result++;
    }
}

int main(void)
{
    char *s = "Hello\nworld\n";
    printf("%d\n", getStringLengthDelta1(s + 5 + 1, strlen(s)));
}

/*int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 1;
    }

    clock_t start = clock();

    HashTable *table = buildHashTable();

    fillTable(table, argv[1]);

    printHashTableRaw(table);

    StringArray *array = getKeys(table);

    // qsort();

    // save

    freeStringArray(array);
    freeHashTable(table);

    clock_t end = clock();
    printf("\nDone, %.02f sec\n", (double) (end - start) / CLOCKS_PER_SEC);

    return 0;
}
*/
