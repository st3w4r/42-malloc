#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdint.h>

#include "malloc.h"
/*
int main(int argc, char **argv) {

	int i;
	int nb;
	char c;
	char *str;
	int page_size;

	nb = atoi(argv[2]);
	c = argv[1][0];
	str = (char*)mmap(0, nb + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	i = 0;

	while(i<nb) {
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);
	page_size = getpagesize();
	printf("%d\n", page_size);

	int success;
	struct rlimit *rlimit;

	rlimit = malloc(sizeof(struct rlimit));

	// printf("Limit: %lu\n", sizeof(struct rlimit));

	success = getrlimit(RLIMIT_NPROC, rlimit);

	printf("Core limit soft: %ju\n", (uintmax_t)rlimit->rlim_cur);
	printf("Core limit soft: %juMB\n", (uintmax_t)rlimit->rlim_cur / 1024 / 1024);
	printf("Core limit hard: %ju\n", (uintmax_t)rlimit->rlim_max);

	return (0);
}
*/


// size_t	get_number_of_pages(size_t page_size, size_t block_size) {
// 	size_t	nb_page;
// 	size_t	nb_allocation;
//
// 	nb_page = 1;
// 	nb_allocation = 0;
//
// 	if (block_size > 0 && page_size > 0){
// 		while (nb_allocation < 100){
// 			nb_allocation = nb_page * page_size / block_size;
// 			nb_page++;
// 		}
// 	}
// 	return nb_page;
// }

// void ft_get_page(size_t size) {
// 	void *first_addr;
// 	int page_numbers;
// 	int page_size;
//
// 	page_size = getpagesize();
//
// 	if (page_size > 0)
// 	{
//
// 	page_number = size / getpagesize();
//
// 	if (size > LIMIT_TINY)
// 	{
//
// 	}
//
// 	first_addr = mmap(0, ,
//
// 	}
// }

void display_memory(void *first_addr) {
	t_block *block;

	block = (t_block*)first_addr;
	printf("----Memory----\n");
	printf("first_addr: %p\n", block->first_addr);
	printf("next_addr: %p\n", block->next_addr);
	printf("used: %d\n", block->used);
	printf("size_data: %lu\n", block->size_data);
	printf("ptr_data: %p\n", block->ptr_data);
}

int main(int argc, char **argv) {
	// first_addr = mmap(0, LIMI
	// printf("%lu\n", sizeof(t_block));

	// void *ptr;
	first_addr = create_empty_zone(TINY_BLOCK);

	printf("%p\n", &first_addr);

	display_memory(first_addr);

}
// void *malloc(size_t size) {
//
// }
//
// void free(void *ptr) {
//
// }
//
// void *realloc(void *ptr, size_t size) {
//
// }
