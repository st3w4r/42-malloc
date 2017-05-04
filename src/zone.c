#include "malloc.h"


void	*create_empty_zone(size_t block_size) {
	size_t allocation_size;
	void *ptr;

	allocation_size = get_allocation_size(block_size);
	ptr = allocation_zone(allocation_size);
	init_zone(ptr, allocation_size, block_size);

	return ptr_zone;
}

size_t get_allocation_size(size_t block_size) {
	size_t nb_page;
	size_t header_size;
	size_t allocation_size;
	size_t page_size;
	void *ptr_zone;

	page_size = getpagesize();
	header_size = sizeof(t_block);
	printf("header_size: %lu\n", header_size);
	printf("block_size: %lu\n", block_size);

	nb_page = get_number_of_pages(page_size, header_size + block_size);
	printf("nb_page: %lu\n", nb_page);
	allocation_size = nb_page * page_size;

	return allocation_size;
}

size_t	get_number_of_pages(size_t page_size, size_t block_size) {
	size_t	nb_page;
	size_t	nb_allocation;

	nb_page = 1;
	nb_allocation = 0;

	if (block_size > 0 && page_size > 0){
		while (nb_allocation < MIN_ALLOCATION_PER_ZONE){
			nb_allocation = nb_page * page_size / block_size;
			nb_page++;
		}
	}
	return nb_page;
}

void *allocate_zone(size_t allocation_size) {
	void *ptr_zone;

	ptr_zone = mmap(0, allocation_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	return ptr_zone;
}

void init_zone(void *first_zone_addr, size_t allocation_size, size_t block_size) {
	// t_block *block;
	// size_t total_size;
	//
	// block = (t_block)ptr;
	// block->first_addr = ptr;
	// block->next_addr =
}

void *init_one_block(void *block_ptr, char type) {
	t_block *block;

	block = (t_block)block_ptr;
	block->first_addr = block_ptr;
	block->next_addr = NULL;
	block->used = 0;
	block->type = type;
	block->ptr_data = block_ptr + sizeof(t_block);

	return block;
}

// void	init_zone(void *first_zone_addr, size_t nb_block, size_t block_size, char type) {
// 	t_block block;
//
// 	block.first_addr = first_zone_addr;
// 	block.next_addr = sizeof(t_block) + block_size;
// 	block.used = 0;
// 	block.type = type;
// 	block.size_data = block_size;
// 	block.ptr_data = first_zone_addr + sizeof(t_block);
// }
//
// void	init_block(void *first_zone_addr, size_t block_size, char type) {
// 	t_block block;
//
// 	block.first_addr = first_zone_addr;
// 	block.next_addr = first_zone_addr + sizeof(t_block) + block_size;
// 	block.used = 0;
// 	block.type = type;
// 	block.size_data = block_size;
// 	block.ptr_data = first_zone_addr + sizeof(t_block);
// }
