#include "../inc/malloc.h"
#include <string.h>
#include <stdio.h>

int main()
{
	char *ptr1;
	char *ptr2;
	char *ptr3;


	ptr1 = malloc(128);
	ptr3 = ptr1;
	strcpy(ptr1, "Hello");
	ptr2 = malloc(128);
	strcpy(ptr2, "Hello");
	free(ptr2);
	ptr1 = realloc(ptr1, 296);

	int i =0;
	while (i < 296) {
		ptr1[i] = 'B';
		i++;
	}
	ptr1[i] = '\0';

	printf("%s\n", ptr1);
	printf("%s\n", ptr2);
	printf("%s\n", ptr3);
	// realloc
	show_alloc_mem();
	return (0);
}
