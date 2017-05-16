#include "malloc.h"

t_block *init_one_block(t_block *block_ptr) {
	t_block *block;

	block = (t_block*)block_ptr;
	block->current_addr = block_ptr;
	block->next_addr = NULL;
	block->is_free = TRUE;
	block->size_data = 0;
	block->ptr_data = block_ptr + sizeof(t_block);

	return block;
}

void set_block_to_used(t_block *block, size_t size_data) {
  block->size_data = size_data;
  block->is_free = FALSE;
}

// void add_block_to_zone(t_zone *zone, t_block *block) {
//   zone->first_block = block;
// }

/*
** Calcul the available space
** If the space is unsufisant return false if the block is added return true
*/

// t_bool check_available_space(t_zone *zone, size_t block_size) {
//
// }


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
  // printf("current_block: %p\n", current_block);
  // printf("next_block: %p\n", current_block->next_addr);
  // while (current_block != NULL) {
  while (current_block != NULL && current_block->is_free == FALSE) {
    current_block = current_block->next_addr;
  }
  // printf("current_block: %p\n", current_block);
  return current_block;
}

t_bool	is_space_available_block(t_block *block, size_t size_data) {
	if (block != NULL && block->size_data >= size_data) {
		return TRUE;
	}
	return FALSE;
}

// t_block *get_block_unused_size(t_block *block, size_t size_data) {
// 	t_block *current_block;
//
// 	current_block = get_block_unused(block);
// 	while (current_block != NULL && is_space_available_block(current_block, size_data) == FALSE) {
// 		current_block = get_block_unused(current_block);
// 	}
// 	return current_block;
// }

t_block *get_reusable_block(t_block *block, size_t size_data) {
  t_block *current_block;

  current_block = block;
  // printf("current_block: %p\n", current_block);
  // printf("next_block: %p\n", current_block->next_addr);
  // while (current_block != NULL) {
  while (current_block != NULL &&
				current_block->is_free == FALSE &&
				current_block->size_data >= size_data) {
    current_block = current_block->next_addr;
  }
  // printf("current_block: %p\n", current_block);
  return current_block;
}


void realease_block(t_block *block) {
  block->is_free = TRUE;
}
/*
** Add new block to the end of the zone
*/
// t_block *add_new_block(t_zone *zone, t_block *block) {
//   t_block *current_block;
//
//   current_block = zone->first_block;
//   while (current_block != NULL) {
//     current_block = current_block->next_addr;
//   }
//   current_block = block;
//   return current_block;
// }



//
// t_block *get_block(t_zone *zone, t_block *block) {
//
// }
