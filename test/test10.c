#include "../inc/malloc.h"
#include <string.h>
#include <stdio.h>

// The output should be "Hel"
int main()
{
	char *ptr1;
	char *ptr2;
	char *ptr3;


	ptr1 = malloc(1024*5);
	ptr2 = malloc(1024*5);
	strcpy(ptr1, "Hello");
	printf("--Before Free--\n");
	show_alloc_mem();
	free(ptr1);
	free(ptr1);
	free(ptr2);
	printf("--After Free--\n");
	show_alloc_mem();
	return (0);
}
