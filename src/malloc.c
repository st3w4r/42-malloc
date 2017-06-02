#include "malloc.h"

/*
** Retrun the right zone or return null no zone available
*/
t_zone *get_right_zone(t_zone *first_zone, size_t size_data) {
  t_zone *current_zone;

  current_zone = first_zone;
  while (current_zone != NULL) {
    if (right_type_zone(current_zone, size_data) == TRUE) {
      return current_zone;
    }
    current_zone = current_zone->next_zone;
  }
  return current_zone;
}

t_block *add_block_to_zone(t_zone *zone, size_t size_data) {
  t_block *block;
  t_block *last_block;

  last_block = get_last_block(zone);
  block = last_block->current_addr + sizeof(t_block) + last_block->size_data;
  block = init_one_block(zone, block, size_data);
  last_block->next_addr = block;
  return block;
}


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
