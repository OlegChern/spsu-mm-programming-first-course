typedef struct BigInt
{
    int digits_count;
    int *digits;
} BigInt;

static const int kBase = 16;

static const int kIniSize = 100;

BigInt *BigIntFrmInt(int _num);

void BigIntOutput(BigInt *num);

void BigIntDelete(BigInt **num);

BigInt *BigIntPow(BigInt *num, int pow);

