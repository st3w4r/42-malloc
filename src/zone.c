#include "malloc.h"

/*
** Get a initialized typed zone
*/
t_zone *get_new_zone(size_t size) {
  t_zone *zone_ptr;

  if (size <= TINY_BLOCK) {
    zone_ptr = create_empty_zone(TINY_BLOCK, TINY);
  } else if (size <= SMALL_BLOCK) {
    zone_ptr = create_empty_zone(SMALL_BLOCK, SMALL);
  } else {
    zone_ptr = create_empty_zone(size, LARGE);
  }
  return zone_ptr;
}

/*
** Create an empty zone and return a pointer on it
** @parm size_t block_size	Get the max size of a block
** @return pointer on the empty zone with header
*/
t_zone	*create_empty_zone(size_t block_size, char type) {
	size_t allocation_size;
	void *ptr_zone;

	if (type == LARGE) {
		allocation_size = block_sizes;
	} else {
		allocation_size = get_allocation_size(block_size);
	}

	ptr_zone = allocate_zone(allocation_size);
	init_zone(ptr_zone, allocation_size, block_size, type);

	return ptr_zone;
}


size_t get_allocation_size(size_t block_size) {
	size_t nb_page;
	size_t block_header_size;
	size_t allocation_size;
	size_t page_size;
	void *ptr_zone;

	page_size = getpagesize();
	block_header_size = sizeof(t_block);
	// printf("block_header_size: %lu\n", block_header_size);
	// printf("block_size: %lu\n", block_size);

	nb_page = get_number_of_pages(page_size, block_header_size + block_size);
	// printf("nb_page: %lu\n", nb_page);
	allocation_size = nb_page * page_size;

	return allocation_size;
}

size_t	get_number_of_pages(size_t page_size, size_t block_size) {
	size_t	nb_page;
	size_t	nb_allocation;

	nb_page = 0;
	nb_allocation = 0;

	if (block_size > 0 && page_size > 0){
		while (nb_allocation < MIN_ALLOCATION_PER_ZONE){
			nb_page++;
			nb_allocation = nb_page * page_size / block_size;
		}
	}
	return nb_page;
}

void *allocate_zone(size_t allocation_size) {
	void *ptr_zone;

	// printf("allocation_size: %lu\n", allocation_size);
	ptr_zone = mmap(0, allocation_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	return ptr_zone;
}

/**
** Add the header to the zone
**/
void init_zone(void *first_zone_addr,
							size_t allocation_size,
							size_t block_size,
							char type) {
	t_zone	*zone;

	zone = (t_zone*)first_zone_addr;
	zone->first_block = first_zone_addr + sizeof(t_zone);
	zone->current_zone = first_zone_addr;
	zone->next_zone = NULL;
	zone->size = allocation_size;
	zone->type = type;
}

// void add_zone_to_tail(t_zone current_zone, t_zone new_zone) {
// 	current_zone->next_zone = new_zone;
// }

// void init_zone(void *first_zone_addr, size_t allocation_size, size_t block_size) {
// 	size_t total_size;
// 	t_block *block;
//
// 	total_size = 0;
//
// 	while (total_size + (block_size + sizeof(t_block)) <= allocation_size) {
// 		block = init_one_block(first_zone_addr + total_size, block_size);
// 		total_size += sizeof(t_block) + block_size;
// 		block->next_addr = first_zone_addr + total_size;
// 	}
// 	block->next_addr = NULL;
//
// }
