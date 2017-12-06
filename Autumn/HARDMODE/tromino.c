#include <stdio.h>

int a[9][12];
long long m[1 << 2 * 9][12];

long long res(int x, int y)
{
    int max;
    if (y == 12)
    return 1;
    if (x == 9)
    {
        int h = 0;
        int y1 = y + 1;
        if (y1 < 11)
            max = y1 + 2;
        else
            max = 12;
        for (; y1 < max; y1++)
            for (x = 0; x < 9; x++)
            {
                h = (h << 1) + a[x][y1];
            }
        if (m[h][y] == 0)
            m[h][y] = res(0, y + 1);
        return m[h][y];
    }
    if (a[x][y] != 0)
        return res(x + 1, y);
    long long k = 0;
    if ((x < 8) && (y < 11) && (a[x + 1][y + 1] == 0) && (a[x][y + 1] == 0))
    {
        a[x + 1][y + 1] = 1;
        a[x][y + 1] = 1;
        a[x][y] = 1;
        k += res(x + 1, y);
        a[x + 1][y + 1] = 0;
        a[x][y + 1] = 0;
        a[x][y] = 0;
    }
    if ((x < 8) && (y < 11) && (a[x + 1][y] == 0) && (a[x][y + 1] == 0))
    {
        a[x + 1][y] = 1;
        a[x][y + 1] = 1;
        a[x][y] = 1;
        k += res(x + 1,y);
        a[x + 1][y] = 0;
        a[x][y + 1] = 0;
        a[x][y] = 0;
    }
    if ((x < 8) && (y < 11) && (a[x + 1][y] == 0) && (a[x + 1][y + 1] == 0))
    {
        a[x + 1][y + 1] = 1;
        a[x + 1][y] = 1;
        a[x][y] = 1;
        k += res(x + 1,y);
        a[x + 1][y] = 0;
        a[x + 1][y + 1] = 0;
        a[x][y] = 0;
    }
    if ((x > 0) && (y < 11) && (a[x - 1][y + 1] == 0) && (a[x][y + 1] == 0))
    {
        a[x - 1][y + 1] = 1;
        a[x][y + 1] = 1;
        a[x][y] = 1;
        k += res(x + 1, y);
        a[x - 1][y + 1] = 0;
        a[x][y + 1] = 0;
        a[x][y] = 0;
    }
    if ((y < 10) && (a[x][y + 1] == 0) && (a[x][y + 2] == 0))
    {
        a[x][y + 1] = 1;
        a[x][y + 2] = 1;
        a[x][y] = 1;
        k += res(x + 1,y);
        a[x][y + 1] = 0;
        a[x][y + 2] = 0;
        a[x][y] = 0;
    }
    if ((x < 7) && (a[x + 1][y] == 0) && (a[x + 2][y] == 0))
    {
        a[x + 1][y] = 1;
        a[x + 2][y] = 1;
        a[x][y] = 1;
        k += res(x + 1,y);
        a[x + 1][y] = 0;
        a[x + 2][y] = 0;
        a[x][y] = 0;
    }
    return k;
}

int main()
{
    printf("%lli\n",res(0,0));

    return 0;
}
