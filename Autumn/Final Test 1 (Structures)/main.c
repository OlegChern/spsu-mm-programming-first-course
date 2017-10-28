#include <stdio.h>
#include <memory.h>

#include "list.h"
#include "str_funcs.h"


int main() {
    printf(
            "╭---------------------------- BEGIN OF USAGE -----------------------------╮\n"
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
            "|        append <value>                                                   |\n"
            "|    Description:                                                         |\n"
            "|        adds value to the end of the list.                               |\n"
            "|    Examples:                                                            |\n"
            "|    >>> print                                                            |\n"
            "|    >>> [1, 2]                                                           |\n"
            "|    >>> append 3                                                         |\n"
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
            "╰---------------------------- END OF USAGE -------------------------------╯\n"
    );

    List *l = NULL;
    char *request = NULL;
    size_t request_len = 0;

    while (1)
    {
        free(request);
        request_len = 0;

        printf(">>> ");
        getline(&request, &request_len, stdin);
        int tmp = 0;
        while (request[tmp] != '\0')
            tmp++;
        request[tmp - 1] = '\0';

        if (strcmp(request, "print") == 0)
        {
            printf(">>> ");
            print_list(l);
            printf("\n");
        }
        else if (starts_with(request, "append "))
        {
            int error;
            int v = parse_int(request + 7, &error);
            if (error)
                printf(">>> <Unrecognized syntax>\n");
            else
                append(&l, v);
        }
        else if (starts_with(request, "at "))
        {
            printf(">>> ");

            int error;
            int pos = parse_int(request + 3, &error);
            if (error)
                printf("<Unrecognized syntax>\n");
            else
            {
                int r = at(l, pos, &error);
                if (error)
                    printf("<Given position don't satisfy list bounds>");
                else
                    printf("%d", r);
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
    free(l);

    return 0;
}