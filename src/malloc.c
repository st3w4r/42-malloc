#include "malloc.h"
//
// void *get_new_zone(size_t size) {
//   void *zone_ptr;
//
//   if (size <= TINY_BLOCK) {
//     zone_ptr = create_empty_zone(TINY_BLOCK, TINY);
//   } else if (size <= SMALL_BLOCK) {
//     zone_ptr = create_empty_zone(SMALL_BLOCK, SMALL);
//   } else {
//     zone_ptr = create_outside_zone(size, LARGE);
//   }
//   return zone_ptr;
// }

// void set_block_to_used(t_block *block, size_t size) {
//   block->size_data = size;
//   block->used = TRUE;
// }

// Issue when the last block is used, this one is returned
// void *get_block_unused(t_block *block) {
//   t_block *current_block;
//
//   current_block = block;
//   while (current_block != NULL && current_block->used != FALSE) {
//     current_block = current_block->next_addr;
//   }
//   return current_block;
// }


void *ft_malloc(size_t) {
  t_zone *first_zone;

  first_zone = (t_zone*)first_addr;
  if (first_zone == NULL) {
    first_zone = get_new_zone(size);
  }
  first_zone = (t_block*)

}

// void *ft_malloc(size_t size) {
//   t_block *first_block;
//   t_block *block;
//
//   if (first_addr == NULL) {
//     first_addr = get_new_zone(size);
//   }
//   first_block = (t_block*)first_addr;
//   block = get_block_unused(first_block);
//   set_block_to_used(block, size);
//   return block;
// }
