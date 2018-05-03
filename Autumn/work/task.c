#include<stdio.h>
#include<stdlib.h>
#define INIT_SIZE 8

typedef struct vector {
    int *data;
    int size;
    int top;
} vect;

vect *createMassive() {
    vect *out = NULL;
    out = malloc(sizeof(vect));
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(int));
    out->top = 0;
    return out;
}

void resize(vect *massive) {
    massive->size += 1;
    massive->data = realloc(massive->data, massive->size * sizeof(int));
}

void addtoend(vect *massive, int value) {
    if (massive->top >= massive->size) {
        resize(massive);
    }
    massive->data[massive->top] = value;
    massive->top++;
}


int last(vect *massive) {
    return massive->data[massive->top - 1];
}


int main()
{
    int i, k, x;
    vect *s = createMassive();
    printf("Please enter a number of elements you want in massive\n");
    scanf("%d", &k);
    printf("Now enter the values of these elements\n");
    for (i = 0; i < k; i++)
    {
        scanf("%d", &x);
        addtoend(s, x);
    }
    printf("Last element is %d", last(s));
    return 0;
}


