#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#define _CRT_NO_WARNINGS

int main()
{
	int i;
	HASHTABLE * ht = create();
	put(ht, "key1", "value1");
	put(ht, "key2", "value2");
	put(ht, "key3", "value3");
	put(ht, "key4", "value4");
	put(ht, "key3", "value5");
	printf("%s\n", (char*)get(ht, "key1"));
	printf("%s\n", (char*)get(ht, "key2"));
	printf("%s\n", (char*)get(ht, "key3"));
	printf("%s\n", (char*)get(ht, "key4"));
	void *f = get(ht, "kkk");
	if (f)
	{
		printf("Error!\n");
	}
	else
	{
		printf("Not found!\n");
	}
	for (i = 0; i<50; i++)
	{
		char *s = calloc(6, 1);
		sprintf_s(s, "ddd%d", i);
		put(ht, s, s);
	}
  
	return 0;
}
