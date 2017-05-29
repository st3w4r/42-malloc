#include "malloc.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dt;
	const char	*sr;
	size_t		i;

	sr = src;
	dt = dest;
	i = 0;
	while (i < n)
	{
		dt[i] = sr[i];
		i++;
	}
	return (dest);
}

void copy_data(t_block *block, t_block *new_block) {
	return ft_memcpy(new_block->ptr_data, block->ptr_data, block->size_data);
}

void	*resize_allocation(t_block *block, size_t new_size) {
	t_block *new_block;

	new_block = NULL;
	if (block->size <= new_size) {
		block->size = new_size;
		new_block = block;
	} else {
		new_block = ft_malloc(new_size);
		if (new_block != NULL) {
			copy_data(block, new_block);
			ft_free(block);
		}
	}
	return new_block;
}

void	*ft_realloc(void *ptr, size_t size) {
	t_block *current_block;
	t_block *new_block;

	current_block = (t_block *)ptr;

	if (right_type_zone(current_block->zone, size) == TRUE) {
		new_block = resize_allocation(current_block, size);
	} else {
		new_block = ft_malloc(new_size);
		if (new_block != NULL) {
			copy_data(block, new_block);
			ft_free(block);
		}
	}
	return new_block;
}
