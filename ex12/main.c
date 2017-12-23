#include <stdio.h>
#include <stdlib.h>

#define BigInt struct BigInt

const unsigned char NUM_BASE = 16; // I chose 16 to do without conversion of the answer

BigInt
{
    unsigned char num;
    BigInt *next;
};

void freeBigInt(BigInt *num)
{
    BigInt *ptr_prv, *ptr;

    ptr = num;

    while (ptr->next != NULL)
    {
        ptr_prv = ptr;
        ptr = ptr->next;

        free(ptr_prv);
    }

    free(ptr);
}

BigInt *createBigInt(unsigned char num)
{
    BigInt *result = malloc(sizeof(BigInt));
    result->num = num;
    result->next = NULL;

    return result;
}

int getSize(BigInt *num)
{
    int k = 1;

    while (num->next != NULL)
    {
        k++;
        num = num->next;
    }

    return k;
}

BigInt *bigMult(BigInt *num1, BigInt *num2)
{
    BigInt *result = malloc(sizeof(BigInt));
    result->num = 0;
    result->next = NULL;

    int size1 = getSize(num1);
    int size2 = getSize(num2);

    BigInt *small, *big;

    if (size1 > size2)
    {
        small = num2;
        big = num1;
    }
    else
    {
        small = num1;
        big = num2;
    }

    BigInt *res_chk = result;

    while (small != NULL)
    {
        unsigned char delta_prv = 0;
        unsigned char delta_next = 0;

        BigInt *big_temp = big;
        BigInt *res_temp = res_chk;


        while (big_temp->next != NULL)
        {
            delta_next = small->num * big_temp->num;

            res_temp->num += delta_next % NUM_BASE + delta_prv;

            delta_prv = delta_next / NUM_BASE + res_temp->num / NUM_BASE;

            res_temp->num %= NUM_BASE;

            if (res_temp->next == NULL)
            {
                res_temp->next = malloc(sizeof(BigInt));
                res_temp->next->num = 0;
                res_temp->next->next = NULL;
            }

            big_temp = big_temp->next;
            res_temp = res_temp->next;
        }

        delta_next = small->num * big_temp->num;

        if (res_temp == NULL)
        {
            res_temp = malloc(sizeof(BigInt));
            res_temp->num = 0;
            res_temp->next = NULL;
        }

        res_temp->num += delta_next % NUM_BASE + delta_prv;

        delta_prv = delta_next / NUM_BASE + res_temp->num / NUM_BASE;

        res_temp->num %= NUM_BASE;

        if (delta_prv != 0)
        {
            if (res_temp->next == NULL)
            {
                res_temp->next = malloc(sizeof(BigInt));
                res_temp->next->num = 0;
                res_temp->next->next = NULL;
            }

            res_temp->next->num += delta_prv;
        }

        small = small->next;
        res_chk = res_chk->next;
    }

    return result;

}

BigInt *bigSum(BigInt *num1, BigInt *num2) // I was able to do without it but still made an implementation
{
    BigInt *result = calloc(1, sizeof(BigInt));
    BigInt *return_value = result;
    result->next = NULL;
    result->num = 0;

    while ((num1->next != NULL) && (num2->next != NULL))
    {
        result->num += num1->num + num2->num;
        result->next = calloc(1, sizeof(BigInt));

        result->next->num = 0;
        result->next->next = NULL;

        if (result->num >= NUM_BASE)
        {
            result->next->num = result->num / NUM_BASE;
            result->num = result->num % NUM_BASE;
        }

        num1 = num1->next;
        num2 = num2->next;
        result = result->next;
    }

    result->num += num1->num + num2->num;

    if (result->num >= NUM_BASE)
    {
        result->next = calloc(1, sizeof(BigInt));
        result->next->next = NULL;
        result->next->num = result->num / NUM_BASE;
        result->num = result->num % NUM_BASE;
    }

    BigInt *cnt = NULL;

    if (num1->next != NULL)
    {
        cnt = num1->next;
    }
    else if (num2->next != NULL)
    {
        cnt = num2->next;
    }

    if (cnt != NULL)
    {
        while (cnt != NULL)
        {
            if (result->next == NULL)
            {

                result->next = calloc(1, sizeof(BigInt));
                result->next->num = 0;
                result->next->next = NULL;

            }

            result = result->next;
            result->num += cnt->num;

            if (result->num >= NUM_BASE)
            {
                if (result->next == NULL)
                {

                    result->next = calloc(1, sizeof(BigInt));
                    result->next->num = 0;
                    result->next->next = NULL;

                }

                result->next->num = result->num / NUM_BASE;
                result->num = result->num % NUM_BASE;
            }

            result = result->next;
            cnt = cnt->next;
        }
    }


    return return_value;
}

BigInt *pow(BigInt *num, int power)
{
    BigInt *temp = malloc(sizeof(BigInt));
    *temp = *num;

    for (int i = 1; i < power; i++)
    {
        *temp = *bigMult(temp, num);
    }

    return temp;
}

void toHex(unsigned char num)
{
    if (num < 10)
        printf("%d", num);
    else
        switch (num)
        {
            case 10:
            {
                printf("a");
                break;
            }
            case 11:
            {
                printf("b");
                break;
            }
            case 12:
            {
                printf("c");
                break;
            }
            case 13:
            {
                printf("d");
                break;
            }
            case 14:
            {
                printf("e");
                break;
            }
            case 15:
            {
                printf("f");
                break;
            }
            default:
            {
                break;
            }
        }

}

void printBigInt(BigInt *num)
{
    if (num->next == NULL)
    {
        if (num->num != 0)
            toHex(num->num);

        return;
    }

    printBigInt(num->next);
    toHex(num->num);
}

int main()
{
    unsigned char num = 3;

    BigInt *answer = createBigInt(num);

    *answer = *pow(answer, 5000);

    printf("The answer is:\n");

    printBigInt(answer);

    freeBigInt(answer);

    return 0;
}