#include "malloc.h"

t_block *init_one_block(void *block_ptr) {
	t_block *block;

	block = (t_block*)block_ptr;
	block->prev_addr = block_ptr;
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
