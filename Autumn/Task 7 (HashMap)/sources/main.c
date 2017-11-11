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
            "|        print_map                                                            |\n"
            "|    Description:                                                         |\n"
            "|        prints current list in format [val1, val2, ..., val_last].       |\n"
            "|    Examples:                                                            |\n"
            "|    >>> # void list                                                      |\n"
            "|    >>> print_map                                                            |\n"
            "|    >>> []                                                               |\n"
            "|    >>> # list 1->2->3                                                   |\n"
            "|    >>> print_map                                                            |\n"
            "|    >>> [1, 2, 3]                                                        |\n"
            "|  * APPEND                                                               |\n"
            "|    Syntax:                                                              |\n"
            "|        put_in_map <value>                                                   |\n"
            "|    Description:                                                         |\n"
            "|        adds value to the end of the list.                               |\n"
            "|    Examples:                                                            |\n"
            "|    >>> print_map                                                            |\n"
            "|    >>> [1, 2]                                                           |\n"
            "|    >>> put_in_map 3                                                         |\n"
            "|    >>> print_map                                                            |\n"
            "|    >>> [1, 2, 3]                                                        |\n"
            "|  * AT                                                                   |\n"
            "|    Syntax:                                                              |\n"
            "|        at <position>                                                    |\n"
            "|    Description:                                                         |\n"
            "|        prints value from specified position. Numeration starts from 0.  |\n"
            "|    Examples:                                                            |\n"
            "|    >>> print_map                                                            |\n"
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
    init_map(&hash_map);
    char *request = NULL;
    size_t request_len = 0;

    while (1)
    {
        free(request);
        request = NULL;
        request_len = 0;

        printf(">>> ");
        getline(&request, &request_len, stdin);
        printf("request_len: %d, request: %s\n", (int) request_len, request);

        char **splitted = NULL;
        size_t splitted_len = 0;
        split(request, &splitted, &splitted_len, ' ', 1);

        /* ---------  debug input -----------
         * if (splitted == NULL) {
            printf("len: 0, NULL\n");
            continue;
        }

        printf("________________\n");
        for (int i = 0; i < splitted_len; ++i) {
            printf("len: %d, str: %s\n", (int) splitted_len, splitted[i]);
        }
        printf("________________\n");

        if (strcmp(splitted[0], "quit") == 0)
            break;
            -------------------------------------*/

        if (strcmp(splitted[0], "print") == 0)
        {
            print_map(hash_map);
            printf("\n");
        }
        else if (strcmp(splitted[0], "put") == 0)
        {
            if (splitted_len < 3)
                printf("Too few arguments: %d when expected 2\n", (int) (splitted_len - 1));
            else if (splitted_len > 3)
                printf("Too many arguments: %d when expected 2\n", (int) (splitted_len - 1));
            else
            {
                if (splitted[1][0])
            }
        }
        else if (strcmp(splitted[0], "get") == 0)
        {
            printf(">>> ");

            int error;
            char *k = parse_word(request + 4);
            if (error)
                printf("Unrecognized syntax\n");
            else
            {
                int result;
                int success = get_from_map(hash_map, k, &result);
                if (!success)
                    printf("There is no such key in map\n");
                else
                    printf("%d", result);
            }

            printf("\n");
        }
        else if (strcmp(splitted[0], "pop") == 0)
        {
            printf(">>> ");

            int error;
            char *k = parse_word(request + 4);
            if (error)
                printf("<Unrecognized syntax>\n");
            else
            {
                int result;
                int success = pop_from_map(hash_map, k, &result);
                if (!success)
                    printf("There is no such key in map\n");
                else
                    printf("%d", result);
            }

            printf("\n");
        }
        else if (strcmp(splitted[0], "quit") == 0) {
            break;
        }
        else
            printf("<Unrecognized syntax>\n");

        for (int i = 0; i < splitted_len; ++i)
            free(splitted[i]);
        free(splitted);
    }

    free(request);
    free_map(hash_map);

    return 0;
}