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

/*
** Check if the zone can get the block
*/
// void *init_block_in_zone(t_zone *zone, t_block *block, size_t size) {
//
// }
// void init_block(t_block *block) {
//   // t_block *block;
//
//   // init_block(block, )
// }
//
// void *init_new_zone() {
//
// }
//
// void *init_first_zone() {
//
// }

/*
** Reuse block and return the block or return NULL
*/
// t_block *resue_block(t_zone *zone, size_t sieze_data) {
//   t_block *block;
//   block = get_reusable_block(zone->first_block, sieze_data);
//   // if (block != NULL) {
//   //   set_block_to_used(block, size);
//   // }
//   return block;
// }
//
// t_block *push_block_to_zone(t_zone *zone, t_block *block, size_t size_data) {
//   t_block *last_block;
//
//   if (is_space_available_zone(zone, size_data) == TRUE) {
//     last_block = get_last_block(first_zone);
//     block = last_block->current_addr + sizeof(t_block) + last_block->size_data;
//     block = init_one_block(block);
//     last_block->next_addr = block;
//     // set_block_to_used(block, size_data);
//     return block;
//   }
//   return NULL;
// }
//
// t_zone *push_zone(t_zone *current_zone, size_t size_data) {
//   t_zone *new_zone;
//
//   new_zone = add_new_zone(current_zone, size_data);
//   return new_zone;
// }

/*
** Set a block
*/
// void set_block(t_zone *zone, size_t size_data) {
//   t_block *block;
//
//   block = reuse_block(zone, size_data);
//   if (!block) {
//     block = push_block_to_zone(zone, size_data);
//   }
//   if
// }

// void new_zone_or_push_to_zone(t_zone *zone, t_block *block, size_t size_data) {
//
// }


/*
** Retrun the right zone or return null no zone available
*/
t_zone *get_right_zone(t_zone *first_zone, size_t size_data) {
  t_zone *current_zone;
  // t_bool found;

  // found = FALSE;
  current_zone = first_zone;
  while (current_zone != NULL) {
    if (right_type_zone(current_zone, size_data) == TRUE) {
        // is_space_available_zone(zone, size_data) == TRUE) {
      // found = TRUE;
      // printf("Space available\n");
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
  current_zone = first_zone;
  block = NULL;
  while (block == NULL) {
    current_zone = get_right_zone(current_zone, size);
    if (current_zone == NULL) {
      current_zone = add_new_zone(first_zone, size);
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

// void *ft_malloc(size_t size) {
// 	t_zone *first_zone;
//   t_zone *new_zone;
//   t_zone *zone;
// 	t_block *block;
// 	t_block *last_block;
//
// 	first_zone = (t_zone*)first_addr;
// 	// printf("first_zone: %p\n", first_zone);
// 	if (first_zone == NULL) {
// 		first_zone = get_new_zone(size);
// 		first_addr = first_zone;
// 		block = init_one_block(first_zone->first_block);
// 	} else {
// 		block = get_reusable_block(first_zone->first_block, size);
// 		if (block == NULL) {
//       zone = get_right_zone(first_zone, size);
//       if (zone) {
//         add_block_to_zone(zone, size);
//         printf("Available zone\n");
//       } else {
//         new_zone = add_new_zone(first_zone, size);
// 				block = init_one_block(new_zone->first_block);
//         printf("No available zone\n");
//       }
// 			// if (is_space_available_zone(first_zone, size) == TRUE) {
// 			// 	last_block = get_last_block(first_zone);
// 			// 	block = last_block->current_addr + sizeof(t_block) + last_block->size_data;
// 			// 	block = init_one_block(block);
// 			// 	last_block->next_addr = block;
// 			// 	printf("Space available\n");
// 			// } else {
// 			// 	printf("No available space\n");
// 			// 	new_zone = add_new_zone(first_zone, size);
// 			// 	block = init_one_block(new_zone->first_block);
// 			// }
// 		}
//   }
//   set_block_to_used(block, size);
//   return block;
// }
		// printf("Get block unused: %p\n", block);
		// if (is_space_available_zone(first_zone, size) == TRUE) {
		// 	if (block == NULL) {
		// 		last_block = get_last_block(first_zone);
		// 		block = last_block->current_addr + sizeof(t_block) + last_block->size_data;
		// 		block = init_one_block(block);
		// 		last_block->next_addr = block;
		// 		printf("Space available\n");
		// 	}
		// 	set_block_to_used(block, size);
		// } else {
		// 	printf("No available space\n");
		// }
	// printf("size: %lu\n", first_zone->size);
	// printf("space available: %lu\n", first_zone->size - sizeof(t_zone));
	// printf("size zone header: %lu\n", sizeof(t_zone));
	// printf("addr: %p\n", first_zone);
	// printf("current_block: %p\n", first_zone->current_zone);
	// printf("first_block: %p\n", first_zone->first_block);

	// block = get_block_unused(first_zone->first_block);

// printf("Addr: %p\n", block);
	// if (block == NULL) {
		// block = get_last_block(first_zone);
		// block = init_one_block(block + block->size_data);
	// }

	// printf("block: %p\n", block);

	// set_block_to_used(block, size);



	// init_one_block(block);
	// set_block_to_used(block, size);


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
