#include "../inc/malloc.h"
#include <string.h>
#include <stdio.h>

// The output should be "Hel"
int main()
{
	char *ptr1;
	char *ptr2;
	char *ptr3;


	ptr1 = malloc(10);
	strcpy(ptr1, "Hello");
	ptr1 = realloc(ptr1, 3);
	ptr1 = realloc(ptr1, 15);

	printf("%s\n", ptr1);
	show_alloc_mem();
	return (0);
}
