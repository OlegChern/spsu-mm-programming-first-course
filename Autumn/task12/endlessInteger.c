#include <stdio.h>

#include "endlessInteger.h"
#include "linkedList.h"

const unsigned int LEFT_BIT = (unsigned int) (1) << 31;
const unsigned long long int INT_MOD = (unsigned long long int) (1) << 32;

EndlessInteger *buildEndlessInteger(unsigned int value)
{
    EndlessInteger *result = buildLinkedList();
    addToList(result, value);
    return result;
}

void printEndlessInteger(EndlessInteger *endlessInteger)
{
    if (endlessInteger == NULL)
    {
        printf("NULL");
        return;
    }
    if (endlessInteger->length == 0)
    {
        printf("Error");
        return;
    }
    if (endlessInteger->length == 1)
    {
        printf("%d", endlessInteger->first->value);
        return;
    }
    printf("<EndlessInteger object at 0x%X>", (unsigned int) endlessInteger);
}

/// Returns whether any digit
/// has been printed or not
int printDigits(Element *current, int firstCall)
{
    // boolean
    int digitsPrinted = 0;
    if (current->next != NULL)
    {
        digitsPrinted = printDigits(current->next, 0);
    }
    if (digitsPrinted)
    {
        printf(HEX_FORMAT_FILL, current->value);
        return 1;
    }
    if (current->value == 0)
    {
        if (firstCall)
            printf("0");
        return 0;
    }
    printf(HEX_FORMAT_FREE, current->value);
    return 1;
}

void printHexEndlessInteger(EndlessInteger *endlessInteger)
{
    if (endlessInteger == NULL)
    {
        printf("NULL");
        return;
    }
    if (endlessInteger->length == 0)
    {
        printf("Error");
        return;
    }
    if (endlessInteger->length == 1)
    {
        printf(HEX_FORMAT_FREE, endlessInteger->first->value);
        return;
    }
    printDigits(endlessInteger->first, 1);
}

int endlessIntegerIsPositive(EndlessInteger *endlessInteger)
{
    return !(endlessInteger->last->value & LEFT_BIT);
}

void negateEndlessInteger(EndlessInteger *endlessInteger)
{

}

void addEndlessInteger(EndlessInteger *first, EndlessInteger *second)
{
    if (first == NULL || second == NULL || first->first == NULL || second->first == NULL
            // TODO: support negative numbers
            || !endlessIntegerIsPositive(first) || !endlessIntegerIsPositive(second))
        return;

    int newLength = first->length > second->length?
                    first->length + 1 :
                    second->length + 1;
    int carry = 0;
    Element *currentFirst = first->first;
    Element *currentSecond = second->first;
    for (int i = 0; i < newLength; i++)
    {
        unsigned long long int sum = currentFirst->value + currentSecond->value + carry;
        currentFirst->value = (unsigned int) (sum % INT_MOD);
        carry = (unsigned int) (sum / INT_MOD);
        if (currentFirst->next == NULL
                && currentSecond->next == NULL
                && carry == 0)
        {
            return;
        }
        if (currentFirst->next == NULL)
            addToList(first, 0);
        // FIXME: remove this workaround
        if (currentSecond->next == NULL)
            addToList(second, 0);
        currentFirst = currentFirst->next;
        currentSecond = currentSecond->next;
    }
}

void subtractEndlessInteger(EndlessInteger *first, EndlessInteger *second)
{
    negateEndlessInteger(second);
    addEndlessInteger(first, second);
    // This line is doubtful, but let's set it back
    negateEndlessInteger(second);
}

void multiplyEndlessInteger(EndlessInteger *first, EndlessInteger *second)
{
    printf("Error: multiplication is not implemetned.\n");
}

void divideEndlessInteger(EndlessInteger *first, EndlessInteger *second)
{
    printf("Error: division is not implemented.\n");
}

/* I initially considered writing
 * #define freeEndlessInteger freeList
 * but decided it was a bad idea later on.
 */
void freeEndlessInteger(EndlessInteger *value)
{
    freeList(value);
}
