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


void display_memory_block(void *addr) {
	t_block *block;
	int i;

	block = (t_block*)addr;
	while (block != NULL) {
		printf("----Memory----\n");
		printf("current_addr: %p\n", block->current_addr);
		printf("next_addr: %p\n", block->next_addr);
		printf("is_free: %d\n", block->is_free);
		printf("size_data: %lu\n", block->size_data);
		// printf("size_block: %lu\n", block->size_block);
		printf("ptr_data: %p\n", block->ptr_data);
		printf("Counter: %d\n", i++);
		block = block->next_addr;
	}
}


void display_memory_zone(t_zone *zone) {
	t_zone *current_zone;
	t_block *block;

	current_zone = zone;
	while (current_zone != NULL) {
		printf("--------Zone--------\n");
		printf("Type: %c\n", current_zone->type);
		printf("Size: %zu\n", current_zone->size);
		block = current_zone->first_block;
		display_memory_block(block);
		printf("-----End Zone-------\n");
		current_zone = current_zone->next_zone;
	}
}

int main(int argc, char **argv) {
	int nb;
	void *ptr;
	void *ptr2;
	void *ptr3;
	void *ptr4;
	void *ptr5;
	void *ptr6;
	// void *ptr4;

	nb = atoi(argv[1]);
	// first_addr = mmap(0, LIMI
	// printf("%lu\n", sizeof(t_block));

	// void *ptr;
	// first_addr = create_empty_zone(TINY_BLOCK);
	first_addr = NULL;
	printf("nb: %d\n", nb);
	ptr = ft_malloc(nb);
	printf("%p\n", ptr);
	// display_memory_block(ptr);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	ptr2 = ft_malloc(nb);
	printf("%p\n", ptr2);
	// display_memory_block(ptr);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );



	ptr3 = ft_malloc(nb);
	printf("%p\n", ptr3);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	ptr4 = ft_malloc(nb);
	printf("%p\n", ptr4);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	ft_free(ptr4);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );


	ptr5 = ft_malloc(nb);
	printf("%p\n", ptr5);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	ptr6 = ft_malloc(nb);
	printf("%p\n", ptr6);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );


	// ft_free(ptr2);
	// ptr3 = ft_malloc(nb);
	// printf("%p\n", ptr3);
	// display_memory_block(ptr);

	// display_memory(first_addr);
	// printf("__________________\n" );
	// ptr4 = ft_malloc(nb);
	// printf("%p\n", &ptr4);
	// display_memory(first_addr);
	// while(42);

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
