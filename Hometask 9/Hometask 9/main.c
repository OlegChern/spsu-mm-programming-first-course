#include <stdio.h>
#include <stdlib.h>
#include "myMemoryManager.h"

int main()
{
	void *ptr1 = myMalloc(30);
	void *ptr2 = myMalloc(20);
	myFree(ptr1);
	ptr1 = myMalloc(30);
	ptr2 = myRealloc(ptr2, 30);
	system("pause");
	return 0;
}