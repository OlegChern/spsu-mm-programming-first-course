#ifndef ENDLESSINTEGER_H
#define ENDLESSINTEGER_H

#include "linkedList.h"

/// Does nothing but providing a beautiful-looking name.
typedef LinkedList EndlessInteger;

EndlessInteger *buildEndlessInteger(int);

/// means first += second
void add(EndlessInteger *, EndlessInteger *);

/// means first -= second
void subtract(EndlessInteger *, EndlessInteger *);

/// means first *= second
void multiply(EndlessInteger *, EndlessInteger *);

/// means first /= second
void divide(EndlessInteger *, EndlessInteger *);

#endif // ENDLESSINTEGER_H
