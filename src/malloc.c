#include "malloc.h"


void *ft_malloc(size_t size) {
  t_zone *first_zone;
  t_zone *current_zone;
  t_block *block;

  first_zone = init_first_zone(size);
  if (first_zone == NULL) return NULL;
  current_zone = first_zone;
  block = NULL;
  while (block == NULL) {
    current_zone = get_right_zone(current_zone, size);
    if (current_zone == NULL) {
      current_zone = add_new_zone(first_zone, size);
      if (current_zone == NULL) return NULL;
      init_one_block(current_zone, current_zone->first_block, size);
    }
    block = get_reusable_block(current_zone->first_block, size);
    if (block == NULL) {
      if (is_space_available_zone(current_zone, size) == TRUE) {
        block = add_block_to_zone(current_zone, size);
      } else {
        current_zone = current_zone->next_zone;
      }
    }
  }
  set_block_to_used(block, size);
  return block->ptr_data;
}
