#include "Allocation.h"

#include "Examples.h"

int main()
{
	init();

	intExample();
	structExample();

	close();
	return 0;
}

void intExample()
{
	printf("[Integer Test]\n\n");
	printf(" MyMalloc  Test: ");

	int *a = (int*)myMalloc(sizeof(int));
	*a = 4;

	printf("%d\n", *a);


	printf(" MyRealloc Test: ");

	a = myRealloc(a, sizeof(int) * 2);
	a[1] = 2;

	printf("%d %d\n", a[0], a[1]);


	printf(" MyFree Test.\n\n");

	myFree(a);

	printf("Done.\n\n");
}

void structExample()
{
	printf("[Struct Test]\n\n");
	printf(" MyMalloc Test:");

	TRANSFORM *transform = (TRANSFORM*)myMalloc(sizeof(TRANSFORM));

	transform->position[0] = 1.0f;
	transform->position[1] = 0.5f;
	transform->position[2] = -1.5f;

	printf("\n Positions:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("   %f\n", transform->position[i]);
	}


	transform->rotation[0] = 0.5f;
	transform->rotation[1] = -0.1f;
	transform->rotation[2] = 0.2f;
	transform->rotation[3] = 1.0f;

	printf("\n Rotations:\n");
	for (int i = 0; i < 4; i++)
	{
		printf("   %f\n", transform->rotation[i]);
	}


	printf("\n MyFree Test.\n\n");

	myFree(transform);

	printf("Done.");
}
