#include "LinkedList.h"
using namespace std;

main()
{
    LinkedList <int, char> llist;
    llist.addToBegin(1, 'c');
    llist.deleteByKey(1);
    llist.addToEnd(3, 'a');
    cout << llist.findByKey(2);
}
