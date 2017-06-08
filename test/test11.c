#include "../inc/malloc.h"
#include <string.h>
#include <stdio.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr2;

	addr1 = (char*)malloc(2000);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char*)malloc(2000);
	free(addr1);
	addr1 = (char*)realloc(addr1, 1500);
	printf("%p\n", addr1);
	return (0);
}
