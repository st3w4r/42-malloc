#include "malloc.h"

t_zone *init_first_zone(size_t size_data) {
  t_zone *first_zone;

  first_zone = (t_zone*)first_addr;
  if (first_zone == NULL) {
    first_zone = get_new_zone(size_data);
    if (first_zone == NULL) {
      return NULL;
    }
    first_addr = first_zone;
    init_one_block(first_zone, first_zone->first_block, size_data);
  }
  return first_zone;
}

t_block *get_block(t_block *block, t_zone *first_zone, size_t size) {
  t_zone *current_zone;

  current_zone = first_zone;
  while (block == NULL) {
    current_zone = get_right_zone(current_zone, size);
    if (current_zone == NULL) {
      current_zone = add_new_zone(first_zone, size);
      if (current_zone == NULL) {
        return NULL;
      }
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
  return block;
}

void *ft_malloc(size_t size) {
  t_zone *first_zone;
  t_block *block;

  first_zone = init_first_zone(size);
  if (first_zone == NULL) {
    return NULL;
  }
  block = NULL;
  block = get_block(block, first_zone, size);
  if (block == NULL) {
    return NULL;
  }
  set_block_to_used(block, size);
  return block->ptr_data;
}
