typedef struct Node
{
    int key;
    int value;
    struct Node* next;
}list;

list* create ( int _key, int data );

void addToEnd( int _key, int data, list* head);

list *lookUp (int _key, list* head);

list *removeElement(int _key, list *head);

list *deleteList(list *head);

void printList( list *head);

void build (int size, list** table);

void output (int size, list** table);

void addElementWithKey (int size, list** table, int _key, int _data);

void deleteElement (int size, list** table, int _key);

void findElement(int size, list** table, int _key);

void deleteTable(int size, list** table);
