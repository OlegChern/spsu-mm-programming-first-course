#include <stdio.h>
#include <malloc.h>

#include "unsignedBignum.h"
#include "util.h"

UBN *buildUBN(unsigned int value)
{
    UBN *result = buildLinkedList();
    addValueToList(result, value);
    return result;
}

UBN *cloneUBN(UBN *ubn)
{
    if (ubn == NULL)
        return NULL;

    UBN *result = buildLinkedList();

    Element *current = ubn->first;

    while (current != NULL)
    {
        addValueToList(result, current->value);
        current = current->next;
    }

    return result;
}

void freeUBN(UBN *ubn)
{
    freeList(ubn);
}

// intentioally hidden from outer scope
// by not being included into unsignedBigNum.h
/// UBN is assumed to be non-zero
/// Element is assumed to be non-null
void printHexUBNDigits(Element *current)
{
    if (current->next != NULL)
    {
        printHexUBNDigits(current->next);
        printf(HEX_FORMAT_FILL, current->value);
        return;
    }

    printf(HEX_FORMAT_FREE, current->value);
}

void printHexUBN(UBN *ubn)
{
    if (isZeroUBN(ubn))
    {
        printf("0");
        return;
    }
    printHexUBNDigits(ubn->first);
}

int isZeroUBN(UBN *ubn)
{
    if (ubn == NULL || ubn->first == NULL)
        return 1;

    Element *current = ubn->first;
    do
    {
        if (current->value != 0)
            return 0;
        current = current->next;
    }
    while (current != NULL);

    return 1;
}

void addUBN(UBN *U, UBN *V)
{
    if (U == NULL || V == NULL || V->length == 0)
        return;

    if (U->length == 0)
        addValueToList(U, 0);

    // "int index" turns out to be redudant
    unsigned int carry = 0;
    Element *UCurrent = U->first;
    Element *VCurrent = V->first;

    while (1)
    {
        unsigned long long int sum = UCurrent->value + carry;
        if (VCurrent != NULL)
            sum += VCurrent->value;

        UCurrent->value = (unsigned int) (sum % INT_MOD);
        carry = (unsigned int) (sum / INT_MOD);

        if (carry == 0 && (VCurrent == NULL || VCurrent->next == NULL))
            break;

        if (UCurrent->next == NULL)
            addValueToList(U, 0);
        UCurrent = UCurrent->next;
        VCurrent = VCurrent->next;
    }
}

void leftShiftUBN(UBN *ubn, unsigned int ammount)
{
    for (int i = 0; i < ammount; i++)
    {
        Element *newElement = buildElement(0);
        newElement->next = ubn->first;
        ubn->first->previous = newElement;
        ubn->first = newElement;
    }
    ubn->length += ammount;
}

void rightShiftUBN(UBN *ubn, unsigned int ammount)
{
    int index = 0;
    while (index < ammount && ubn->length != 0)
    {
        free(popFirst(ubn));
        index++;
    }
    if (ubn->length == 0)
        addValueToList(ubn, 0);
}

/// Karatsuba algorithm
void multiplyUBN(UBN *U, UBN *V)
{
    if (isZeroUBN(U))
        return;

    if (isZeroUBN(V))
    {
        freeListContents(U);
        U->first = buildElement(0);
        U->last = U->first;
        U->length = 1;
        return;
    }

    if (U->length == 1 && V->length == 1)
    {
        // No overflow can ever happen here
        unsigned long long int prod = U->first->value + V->first->value;
        U->first->value = (unsigned int) (prod % INT_MOD);
        unsigned int carry = (unsigned int) (prod / INT_MOD);
        if (carry != 0)
            addValueToList(U, carry);
        return;
    }

    // Select base in which booth numbers
    // contain no more than 2 digits.
    // This is done by splitting the bigger number
    // into two roughly equal halves.
    // base = (2^32)^B, where B:
    unsigned int B = U->length > V->length ?
                     U->length / 2 + U->length % 2 :
                     V->length / 2 + V->length % 2;

}

void squareUBN(UBN *ubn)
{
    // TODO: implemetn squareUBN
}

void powerUBN(UBN *ubn, unsigned int power)
{
    if (power == 0)
    {
        freeListContents(ubn);
        ubn->first = buildElement(1);
        ubn->last = ubn->first;
        ubn->length = 1;
        return;
    }

    UBN *result = cloneUBN(ubn);
    do
    {
        if ((power & 1) != 0)
            multiplyUBN(result, ubn);

        squareUBN(result);
        power >>= 1;
    }
    while (power != 0);
}
