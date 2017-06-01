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
		allocation_size = block_size; // Add block_header_size ?
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

t_bool	is_space_available_zone(t_zone *zone, size_t size_data_block) {
	t_block	*last_block;
	void		*max_addr;
	void		*next_addr;


	last_block = get_last_block(zone);

	// printf("current_zone: %p\n", zone->current_zone);
	// printf("last_block: %p\n", last_block->current_addr);

	max_addr = zone->current_zone + zone->size;
	// printf("Current addr: %p\n", zone->current_zone);
	// printf("Max addr: %p\n", max_addr);

	// next_addr = last_block->current_addr + sizeof(t_block) + size_data_block;
	next_addr = last_block->ptr_data + last_block->size_data + sizeof(t_block) + size_data_block;
	// next_addr = last_block->current_addr + sizeof(t_block) + last_block->size_data + sizeof(t_block) + size_data_block;

	// printf("next_addr: %p\n", next_addr);
	// printf("max_addr: %p\n", max_addr);
	// printf("Size data block: %zu\n", size_data_block);
	if (next_addr > max_addr) {
		return FALSE;
	}
	return TRUE;
}


/*
** Add a new zone as next zone, return the new zone or NULL
*/
t_zone  *add_new_zone(t_zone *zone, size_t size_data) {
	t_zone *current_zone;

	if (zone == NULL) {
		return NULL;
	}
	current_zone = zone;
	while (current_zone->next_zone != NULL) {
		current_zone = current_zone->next_zone;
	}
	current_zone->next_zone = get_new_zone(size_data);
	return current_zone->next_zone;
}


/*
** Send data size and a zone, return True if the zone can get this size of data
*/
t_bool right_type_zone(t_zone *zone, size_t size_data) {
	t_bool result;

	result = FALSE;
	if (zone && zone->type) {
		if (zone->type == 'T' && size_data <= TINY_BLOCK) {
			result = TRUE;
		} else if (zone->type == 'S' && size_data > TINY_BLOCK && size_data <= SMALL_BLOCK) {
			result = TRUE;
		} else if (zone->type == 'L' && size_data > SMALL_BLOCK) {
			result = TRUE;
		} else {
			result = FALSE;
		}
	}
	return result;
}

/*
** Return TRUE if all block is free in the zone or false if not
*/
t_bool zone_is_empty(t_zone *zone) {
	t_block *block;

	// if (zone == NULL) {
	// 	return FALSE;
	// }
	block = zone->first_block;
	while (block != NULL) {
		if (block->is_free == FALSE) {
			return FALSE;
		}
		block = block->next_addr;
	}
	return TRUE;
}

void release_zone(t_zone *zone) {
	int result;

	result = munmap(zone->current_zone, zone->size);
}

void release_empty_zone(t_zone *first_zone) {
	t_zone *current_zone;
	t_zone *previous_zone;
	t_zone *next_zone;

	current_zone = first_zone;
	previous_zone = NULL;
	next_zone = NULL;
	while (current_zone != NULL) {
		next_zone = current_zone->next_zone;
		if (zone_is_empty(current_zone) == TRUE) {
			release_zone(current_zone);
			if (previous_zone == NULL) {
				first_addr = next_zone;
			} else {
				previous_zone->next_zone = next_zone;
			}
		} else {
			previous_zone = current_zone;
		}
		current_zone = next_zone;
	}
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
