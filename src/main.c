#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdint.h>
#include <string.h>

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

	i = 0;
	block = (t_block*)addr;
	while (block != NULL) {
		printf("----Memory----\n");
		printf("current_addr: %p\n", block->current_addr);
		printf("next_addr: %p\n", block->next_addr);
		printf("is_free: %d\n", block->is_free);
		printf("size_data: %lu\n", block->size_data);
		// printf("size_block: %lu\n", block->size_block);
		printf("ptr_data: %p\n", block->ptr_data);
		printf("end block: %p\n", block->ptr_data + block->size_data);
		printf("Counter: %d\n", i++);
		block = block->next_addr;
	}
}


void display_memory_zone(t_zone *zone) {
	t_zone *current_zone;
	t_block *block;

	printf("ZONE: %p\n", zone);
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

void display_zone_list(t_zone *zone) {
	t_zone *current_zone;
	int i;

	i = 0;
	current_zone = zone;
	while (current_zone != NULL) {
		printf("Zone: %i Type: %c Size: %zu Addr: %p MaxAddr: %p\n", i, current_zone->type, current_zone->size, current_zone, current_zone->current_zone + current_zone->size);
		i++;
		current_zone = current_zone->next_zone;
	}
}

void multiple_malloc(int size) {
	void *ptr;

	ptr = ft_malloc(size);
	// ptr = malloc(size);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );

}

int main(int argc, char **argv) {
	int nb;
	int nb_malloc;
	void *ptr;
	void *ptr2;
	void *ptr3;
	void *ptr4;
	void *ptr5;
	void *ptr6;
	// void *ptr4;

	nb = atoi(argv[1]);
	nb_malloc = atoi(argv[2]);
	// first_addr = mmap(0, LIMI
	// printf("%lu\n", sizeof(t_block));

	// void *ptr;
	// first_addr = create_empty_zone(TINY_BLOCK);
	// first_addr = NULL;

	/**
	* Realloc feature
	*/
	// ptr = ft_malloc(30);
	// // ptr2 = ft_malloc(10);
	// // ptr3 = ft_malloc(50);
	// // ptr4 = ft_malloc(50);
	// // ft_free(ptr2);
	//
	// ptr = strcpy(ptr, "Hello!\0");
	// ptr = ft_realloc(ptr, 31);
	//
	// // ptr = memset(ptr, '\0',87);
	// // ptr = memset(ptr, 'Y', 87);
	// printf("Sentence: %s\n", ptr);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );
	// return 0;
	/**
	// Multiple malloc
	*/
	int i = 0;
	while (i < nb_malloc) {
		multiple_malloc(nb);
		++i;
	}
	// ft_malloc(40);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );
	display_zone_list((t_zone*)first_addr);
	printf("__________________\n" );

	show_alloc_mem();
	return 0;

	// printf("%d\n", nb);
	// ptr = ft_malloc(42);
	// printf("Ptr: %p\n", ptr);
	// ptr = ft_realloc(ptr, nb);
	// printf("Ptr: %p\n", ptr);
	//
	// return 0;

	// printf("nb: %d\n", nb);
	// ptr = ft_malloc(nb);
	// printf("%p\n", ptr);
	// // display_memory_block(ptr);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );

	// ptr2 = ft_malloc(nb);
	// printf("%p\n", ptr2);
	// // display_memory_block(ptr);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );
	//
	//
	//
	// ptr3 = ft_malloc(nb);
	// printf("%p\n", ptr3);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );
	//
	// ptr4 = ft_malloc(nb);
	// printf("%p\n", ptr4);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );
	// // //
	// // ft_free(ptr4);
	// // display_memory_zone((t_zone*)first_addr);
	// // printf("__________________\n" );
	// //
	// ptr5 = ft_malloc(nb);
	// printf("%p\n", ptr5);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );

	//
	// ptr6 = ft_malloc(nb);
	// printf("%p\n", ptr6);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );
	//
	// ft_free(ptr6);
	// display_memory_zone((t_zone*)first_addr);

	// void *ptr7 = ft_malloc(nb);
	// void *ptr8 = ft_malloc(nb);
	// void *ptr9 = ft_malloc(nb);
	// void *ptr10 = ft_malloc(nb);
	// void *ptr11 = ft_malloc(nb);
	// void *ptr12 = ft_malloc(nb);
	// void *ptr13 = ft_malloc(nb);
	// void *ptr14 = ft_malloc(nb);
	// void *ptr15 = ft_malloc(nb);
	//
	// ft_free(ptr10);
	// ft_free(ptr11);
	// ft_free(ptr12);
	// ft_free(ptr13);

	// ft_free(ptr);
	// ft_free(ptr2);
	// ft_free(ptr3);
	// ft_free(ptr4);
	// ft_free(ptr5);
	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );

	// Realloc
	ft_malloc(48847);
	ft_malloc(3725);

	ptr = ft_malloc(42);
	ptr2 = ft_realloc(ptr, 84);

	ptr = strcpy(ptr, "Hello!\0");
	// printf("%zu\n", ((t_block*)ptr)->size_data);
	// printf("Ptr data: %p\n", ptr);
	printf("Sentence: %s\n", ptr);
	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	// ptr = ft_realloc(ptr, 5000);

	// display_memory_zone((t_zone*)first_addr);
	// printf("__________________\n" );

	// ptr = ft_realloc(ptr, 42);
	printf("Sentence: %s\n", ptr);

	display_memory_zone((t_zone*)first_addr);
	printf("__________________\n" );

	// Test NULL
	ft_free(NULL);

	printf("__________________\n" );
	display_zone_list((t_zone*)first_addr);
	// while(42);



	show_alloc_mem();

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
