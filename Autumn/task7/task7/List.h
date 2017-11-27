typedef struct list
{
	int key;
	int value;
	struct list *next;
} list;


/*check if the list contains key*/
int contain(list *first, int key);

/*add key and value to the list. If the element was added to return 1, else (key is already in the list) return 0*/
int addFirstElement(list **first, int key, int value);

/*delete key from the list. If the element was deleted to return 1, else (key isn't in the list) return 0*/
int deleteElement(list **first, int key);

/*print list*/
void printList(list *first);

/*delete list*/
void deleteList(list **first);

/*get value by key. If the value is found, correct = 1, else correct = 0*/
int getValueByKey(list *first, int key, int *correct);

/*check if the methods of the list work correctly*/
int testList();
