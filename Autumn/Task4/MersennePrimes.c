#include<stdio.h>
#include<math.h>

int prime(long x)
{
    int i;
    for (i = 2; i < sqrt(x); ++i)
    {
        if(x % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    printf("Here are some Mersenne numbers\n");
    int i;
    for (i = 2; i <= 31; ++i)
    {
        long m = pow(2,i)-1;
        if(prime(m))
        {
          printf("%li\n", m);
        }
    }
    return 0;
}
