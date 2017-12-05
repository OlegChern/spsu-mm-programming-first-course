typedef struct longNumber longNumber;


/*convert int to longNumber*/
longNumber *createLongNumberFromInt(int intNumber);

/*print longNumber*/
void printNumber(longNumber *number);

/*delete longNumber*/
void deleteNumber(longNumber **number);

/*return the result of addition of first and second*/
longNumber *addition(longNumber *first, longNumber *second);

/*return the result of multiplication of first and second*/
longNumber *multiplication(longNumber *first, longNumber *second);

/*raise number to power*/
longNumber *raiseToPower(longNumber *number, int power);
