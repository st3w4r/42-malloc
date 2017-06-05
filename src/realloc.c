#include "malloc.h"

void		*copy_data_size(void *dst, const void *src, size_t dst_size, size_t src_size)
{
	char		*char_dst;
	const char	*char_src;
	size_t		i;

	char_src = src;
	char_dst = dst;
	i = 0;
	while (i < src_size && i < dst_size)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}

void	*copy_data(t_block *block, t_block *new_block) {
	return copy_data_size(new_block->ptr_data, block->ptr_data,
									new_block->size_data, block->size_data);
}

t_bool block_fusion(t_block *block, size_t new_size) {
	t_block	*block_next;
	size_t	available_space;

	available_space = 0;
	if (block != NULL) {
		block_next = (t_block*)block->next_addr;
		if (block_next != NULL && block_next->is_free == TRUE) {
				available_space = (block->size_data
					+ sizeof(t_block) + block_next->size_data);
				if (available_space >= new_size) {
					return TRUE;
				}
			}
		}
	return FALSE;
}

t_block	*resize_allocation(t_block *block, size_t new_size) {
	t_block *new_block;
	void *ptr_data;

	new_block = NULL;
	if (block->size_data >= new_size) {
		block->size_data = new_size;
		new_block = block;
	} else if (block_fusion(block, new_size) == TRUE) {
		block->size_data = new_size;
		new_block = block;
		if ((t_block*)block->next_addr != NULL) {
			new_block->next_addr = ((t_block*)block->next_addr)->next_addr;
		}
	} else {
		ptr_data = ft_malloc(new_size);
		if (ptr_data == NULL) return NULL;
		new_block = (t_block *)(ptr_data - sizeof(t_block));
		if (new_block != NULL) {
			copy_data(block, new_block);
			ft_free(block->ptr_data);
		}
	}
	return new_block;
}

void	*ft_realloc(void *ptr, size_t size) {
	t_block	*current_block;
	t_block	*new_block;
	t_zone	*current_zone;
	void *ptr_data;

	if (ptr == NULL || first_addr == NULL || ptr < first_addr) return NULL;
	current_block = (t_block*)(ptr - sizeof (t_block));
	current_zone = (t_zone*)current_block->zone;

	if (right_type_zone(current_zone, size) == TRUE) {
		new_block = resize_allocation(current_block, size);
		if (new_block == NULL) return NULL;
	} else {
		ptr_data = ft_malloc(size);
		if (ptr_data == NULL) return NULL;
		new_block = (t_block *)(ptr_data - sizeof(t_block));
		if (new_block != NULL) {
			copy_data(current_block, new_block);
			ft_free(current_block->ptr_data);
		}
	}
	return new_block->ptr_data;
}
