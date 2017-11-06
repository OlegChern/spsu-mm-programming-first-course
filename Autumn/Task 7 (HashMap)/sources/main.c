#include <stdio.h>
#include <string.h>

#include "../headers/hash_map.h"
#include "../headers/str_funcs.h"


int main() {
    printf(
            "#---------------------------- BEGIN OF USAGE -----------------------------#\n"
            "| Program provide operating with dynamic size list. It works with integer |\n"
            "| type and supports three operations:                                     |\n"
            "|  * PRINT                                                                |\n"
            "|    Syntax:                                                              |\n"
            "|        print                                                            |\n"
            "|    Description:                                                         |\n"
            "|        prints current list in format [val1, val2, ..., val_last].       |\n"
            "|    Examples:                                                            |\n"
            "|    >>> # void list                                                      |\n"
            "|    >>> print                                                            |\n"
            "|    >>> []                                                               |\n"
            "|    >>> # list 1->2->3                                                   |\n"
            "|    >>> print                                                            |\n"
            "|    >>> [1, 2, 3]                                                        |\n"
            "|  * APPEND                                                               |\n"
            "|    Syntax:                                                              |\n"
            "|        put <value>                                                   |\n"
            "|    Description:                                                         |\n"
            "|        adds value to the end of the list.                               |\n"
            "|    Examples:                                                            |\n"
            "|    >>> print                                                            |\n"
            "|    >>> [1, 2]                                                           |\n"
            "|    >>> put 3                                                         |\n"
            "|    >>> print                                                            |\n"
            "|    >>> [1, 2, 3]                                                        |\n"
            "|  * AT                                                                   |\n"
            "|    Syntax:                                                              |\n"
            "|        at <position>                                                    |\n"
            "|    Description:                                                         |\n"
            "|        prints value from specified position. Numeration starts from 0.  |\n"
            "|    Examples:                                                            |\n"
            "|    >>> print                                                            |\n"
            "|    >>> [1, 2, 3]                                                        |\n"
            "|    >>> at 1                                                             |\n"
            "|    >>> 2                                                                |\n"
            "|  * QUIT                                                                 |\n"
            "|    Syntax:                                                              |\n"
            "|        quit                                                             |\n"
            "|    Description:                                                         |\n"
            "|        Exit the program.                                                |\n"
            "#---------------------------- END OF USAGE -------------------------------#\n"
    );

    Hash_map *hash_map = NULL;
    init(&hash_map);
    char *request = NULL;
    size_t request_len = 0;

    while (1)
    {
        free(request);
        request = NULL;
        request_len = 0;

        printf(">>> ");
        getline(&request, &request_len, stdin);

        if (strcmp(request, "print") == 0)
        {
            printf(">>> ");
            print(hash_map);
            printf("\n");
        }
        else if (starts_with(request, "put "))
        {
            int error;
            char *k = parse_word(request + 4);
            int v = parse_int(request + 4 + strlen(k), &error);
            if (error)
                printf(">>> <Unrecognized syntax>\n");
            else
                put(hash_map, v, k);
        }
        else if (starts_with(request, "get "))
        {
            printf(">>> ");

            int error;
            char *k = parse_word(request + 4);
            if (error)
                printf("<Unrecognized syntax>\n");
            else
            {
                int result;
                int success = get(hash_map, k, &result);
                if (!success)
                    printf("There is no such key in map\n");
                else
                    printf("%d", result);
            }

            printf("\n");
        }
        else if (starts_with(request, "pop "))
        {
            printf(">>> ");

            int error;
            char *k = parse_word(request + 4);
            if (error)
                printf("<Unrecognized syntax>\n");
            else
            {
                int result;
                int success = pop(hash_map, k, &result);
                if (!success)
                    printf("There is no such key in map\n");
                else
                    printf("%d", result);
            }

            printf("\n");
        }
        else if (strcmp(request, "quit") == 0) {
            break;
        }
        else
            printf("<Unrecognized syntax>\n");
    }

    free(request);
    free_map(hash_map);

    return 0;
}