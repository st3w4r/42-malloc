#include "../inc/malloc.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	size_t nb;
	int i;
	char *addr;

	if (argc != 2)
	{
		return 0;
	}
	nb = atoi(argv[1]);




	i = 0;
	while (i < nb)
	{
		addr = (char*)malloc(nb);
		addr[0] = 42;
		i++;
	}

	// nb = atoi(argv[1]);
	// ptr = NULL;
	// ptr = malloc(nb);

	// printf("%p\n", ptr);
	// printf("%zu\n", (size_t)nb);
	// malloc(1024 * 32);
	// malloc(1024 * 1024);
	// malloc(1024 * 1024 * 16);
	// malloc(1024 * 1024 * 128);
	// ft_puthexa((uint64_t)ptr);
	// show_alloc_mem();
	return (0);
}
