#include "malloc.h"

void		*ft_memcpy(void *dst, const void *src, size_t dst_size, size_t src_size)
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
	return ft_memcpy(new_block->ptr_data, block->ptr_data,
									new_block->size_data, block->size_data);
}

t_block	*resize_allocation(t_block *block, size_t new_size) {
	t_block *new_block;
	void *ptr_data;

	new_block = NULL;
	if (block->size_data > new_size) {
		block->size_data = new_size;
		new_block = block;
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

	if (ptr == NULL) return NULL;
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
