#include <stdio.h>
#include <string.h>

#include "../headers/hash_map.h"
#include "../headers/str_funcs.h"

#define INIT_LEN 1


int main()
{
    printf(
            "#---------------------------- BEGIN OF USAGE -----------------------------#\n"
            "| Program provide operating with hash map which consist of pairs          |\n"
            "| key/value: key is a not empty string consisted of latin letters and     |\n"
            "| value is an integer number. Map supports 4 operations:                  |\n"
            "|  * print                                                                |\n"
            "|    Syntax:                                                              |\n"
            "|        print                                                            |\n"
            "|    Description:                                                         |\n"
            "|        prints current hash map in format                                |\n"
            "|        [                                                                |\n"
            "|          {key1: value1},                                                |\n"
            "|          {key2: value2},                                                |\n"
            "|          ...                                                            |\n"
            "|          {keyN: valueN},                                                |\n"
            "|        ]                                                                |\n"
            "|  * put                                                                  |\n"
            "|    Syntax:                                                              |\n"
            "|        put <key> <value>                                                |\n"
            "|    Description:                                                         |\n"
            "|        adds value to the map by key if key is not already exist or      |\n"
            "|        changes value by key if key is already exist.                    |\n"
            "|  * get                                                                  |\n"
            "|    Syntax:                                                              |\n"
            "|        get <key>                                                        |\n"
            "|    Description:                                                         |\n"
            "|        returns value by given key if key is already exist.              |\n"
            "|  * pop                                                                  |\n"
            "|    Syntax:                                                              |\n"
            "|        pop <key>                                                        |\n"
            "|    Description:                                                         |\n"
            "|        removes element by given key if key is already exist.            |\n"
            "|                                                                         |\n"
            "| Print 'quit' or 'exit' (without quotes) leave the program.              |\n"
            "#---------------------------- END OF USAGE -------------------------------#\n"
    );

    Hash_map *map = NULL;
    init_map(&map, INIT_LEN);
    char *request = NULL;
    size_t request_len = 0;

    while (1)
    {
        free(request);
        request = NULL;
        request_len = 0;

        printf(">>> ");
        getline(&request, &request_len, stdin);

        char **splitted = NULL;
        size_t splitted_len = 0;
        split(request, &splitted, &splitted_len, ' ', 1);

        if (strcmp(splitted[0], "print") == 0)
        {
            if (splitted_len != 1)
                printf("Unrecognized syntax\n");
            else
                print_map(map);
        }
        else if (strcmp(splitted[0], "put") == 0)
        {
            if (splitted_len - 1 < 2)
                printf("Error: Too few arguments: %d when expected 2\n", (int) (splitted_len - 1));
            else if (splitted_len - 1 > 2)
                printf("Error: Too many arguments: %d when expected 2\n", (int) (splitted_len - 1));
            else
            {
                char *key = splitted[1];
                int error = 0;
                int val = parse_int(splitted[2], &error);

                if (!is_consisted_of_letters(splitted[1]))
                    printf("Error: Wrong key: should be not empty and consisted of only latin letters\n");
                else if (error)
                {
                    if (error == EMPTY)
                        printf("Error: Wrong value: empty value was given\n");
                    else if (error == NAN)
                        printf("Error: Wrong value: value is not a number\n");
                    else if (error == TOO_BIG)
                        printf("Error: Wrong value: too big number for int type\n");
                }
                else
                {
                    if (!put_in_map(&map, key, val))
                        printf("Error: not enough memory\n");
                }
            }
        }
        else if (strcmp(splitted[0], "get") == 0)
        {
            if (splitted_len - 1 < 1)
                printf("Error: Too few arguments: %d when expected 1\n", (int) (splitted_len - 1));
            else if (splitted_len - 1 > 1)
                printf("Error: Too many arguments: %d when expected 1\n", (int) (splitted_len - 1));
            else
            {
                char *key = splitted[1];

                if (!is_consisted_of_letters(splitted[1]))
                    printf("Error: Wrong key: should be not empty and consisted of only latin letters\n");
                else
                {
                    int result;
                    if (!get_from_map(map, key, &result))
                        printf("Error: no such key in map\n");
                    else
                        printf("%d\n", result);
                }
            }
        }
        else if (strcmp(splitted[0], "pop") == 0)
        {
            if (splitted_len - 1 < 1)
                printf("Error: Too few arguments: %d when expected 1\n", (int) (splitted_len - 1));
            else if (splitted_len - 1 > 1)
                printf("Error: Too many arguments: %d when expected 1\n", (int) (splitted_len - 1));
            else
            {
                char *key = splitted[1];

                if (!is_consisted_of_letters(splitted[1]))
                    printf("Error: Wrong key: should be not empty and consisted of only latin letters\n");
                else
                {
                    int result;
                    if (!pop_from_map(map, key, &result))
                        printf("Error: no such key in map\n");
                    else
                        printf("%d\n", result);
                }
            }
        }
        else if (strcmp(splitted[0], "quit") == 0 || strcmp(splitted[0], "exit") == 0)
        {
            if (splitted_len != 1)
                printf("Unrecognized syntax\n");
            else
                break;
        }
        else
            printf("<Unrecognized syntax>\n");

        for (int i = 0; i < splitted_len; ++i)
            free(splitted[i]);
        free(splitted);
    }

    free(request);
    free_map(&map);

    return 0;
}