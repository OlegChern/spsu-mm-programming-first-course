#include <stdio.h>

const int fio = 528;

void binary(unsigned long long int num, int k, int max) //recursively prints the remainders of the division by two; num is the number, k is the counter, max is the size (4 or 8 bytes)
{
    if (k == (max - 1))
    {
        printf("%llu", num % 2);
    }
    else
    {
        k++;
        binary(num / 2, k, max);
        if ((max - k) % 8 == 0)
        {
            printf(" ");
        }
        printf("%llu", num % 2);
    }
}


int main() {

    float temp1 = fio;
    unsigned int *second = (unsigned int*) &temp1;

    double temp2 = -fio;
    unsigned long long int *third = (unsigned long long int*) &temp2;

    int temp3 = -fio;
    unsigned int *first = (unsigned int*) &temp3;

    printf("%s\n%s", "Name: Oleg Nickolaevich Chernyavsky", "Composition of the lengths: 12*4*11 = 528");

    printf("\n%s", "Answer for the first task:  ");
    binary(*first, 0, 32);

    printf("\n%s", "Answer for the second task: ");
    binary(*second, 0, 32);

    printf("\n%s", "Answer for the third task:  ");
    binary(*third, 0, 64);

    return 0;
}
