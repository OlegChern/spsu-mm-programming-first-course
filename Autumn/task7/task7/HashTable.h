#define length 3

typedef struct hashTable hashTable;


/*check if the table contains key*/
int containInTable(hashTable *table, int key);

/*add key and value to the table. If the element was added to return 1, else (key is already in the table) return 0*/
int addInTable(hashTable **table, int key, int value);

/*delete key from the table. If the element was deleted to return 1, else (key isn't in the table) return 0*/
int deleteFromTable(hashTable **table, int key);

/*get value by key. If the value is found, correct = 1, else correct = 0*/
int getValue(hashTable *table, int key, int *correct);

/*print table*/
void printTable(hashTable *table);

/*delete table*/
void deleteTable(hashTable **table);

/*check if the methods of the table work correctly*/
int testTable();
