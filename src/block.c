#include "malloc.h"

t_block *init_one_block(t_zone *zone, void *block_ptr, size_t size_data) {
	t_block *block;

	block = (t_block*)block_ptr;
	block->zone = zone;
	block->current_addr = block_ptr;
	block->next_addr = NULL;
	block->is_free = TRUE;
	block->size_data = size_data;
	block->ptr_data = block_ptr + sizeof(t_block);
	return block;
}

void set_block_to_used(t_block *block, size_t size_data) {
  block->size_data = size_data;
  block->is_free = FALSE;
}

t_block *get_last_block(t_zone *zone) {
  t_block *current_block;

  current_block = zone->first_block;
  while (current_block->next_addr != NULL) {
    current_block = current_block->next_addr;
  }
  return current_block;
}

/*
** Get a unsed block, return NULL if no block is available
*/
t_block *get_block_unused(t_block *block) {
  t_block *current_block;

  current_block = block;
  while (current_block != NULL && current_block->is_free == FALSE) {
    current_block = current_block->next_addr;
  }
  return current_block;
}

t_bool	is_space_available_block(t_block *block, size_t size_data) {
	if (block != NULL && block->size_data >= size_data) {
		return TRUE;
	}
	return FALSE;
}

/*
** Get a unsued block and a block with engouh space, if nothing available return NULL
*/
t_block *get_reusable_block(t_block *block, size_t size_data) {
	t_block *current_block;

	current_block = get_block_unused(block);
	while (current_block != NULL &&
		is_space_available_block(current_block, size_data) == FALSE) {
		current_block = get_block_unused(current_block->next_addr);
	}
	return current_block;
}


void release_block(t_block *block) {
  block->is_free = TRUE;
}
