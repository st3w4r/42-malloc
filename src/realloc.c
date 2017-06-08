/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:27 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 17:17:46 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*copy_data_size(void *dst, const void *src, size_t dst_size,
											size_t src_size)
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

/*
** void	*copy_data(t_block *block, t_block *new_block)
** {
** 	return (copy_data_size(new_block->ptr_data, block->ptr_data,
** 									new_block->size_data, block->size_data));
** }
*/

t_bool	block_fusion(t_block *block, size_t new_size)
{
	t_block	*block_next;
	size_t	available_space;

	available_space = 0;
	if (block != NULL)
	{
		block_next = (t_block*)block->next_addr;
		if (block_next != NULL && block_next->is_free == TRUE)
		{
			available_space = (block->size_data + sizeof(t_block) +
													block_next->size_data);
			if (available_space >= new_size)
			{
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

t_block	*new_allocation(t_block *block, size_t new_size)
{
	t_block	*new_block;
	void	*ptr_data;

	ptr_data = NULL;
	ptr_data = malloc(new_size);
	if (ptr_data == NULL)
	{
		return (NULL);
	}
	new_block = (t_block *)(ptr_data - sizeof(t_block));
	if (new_block != NULL)
	{
		copy_data_size(new_block->ptr_data, block->ptr_data,
										new_block->size_data, block->size_data);
		free(block->ptr_data);
	}
	return (new_block);
}

t_block	*resize_allocation(t_block *block, size_t new_size)
{
	t_block	*new_block;

	new_block = NULL;
	if (block->size_data >= new_size)
	{
		block->size_data = new_size;
		new_block = block;
	}
	else if (block_fusion(block, new_size) == TRUE)
	{
		block->size_data = new_size;
		new_block = block;
		if ((t_block*)block->next_addr != NULL)
		{
			new_block->next_addr = ((t_block*)block->next_addr)->next_addr;
		}
	}
	else
	{
		new_block = new_allocation(block, new_size);
	}
	return (new_block);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*current_block;
	t_block	*new_block;
	t_zone	*current_zone;

	if (ptr == NULL || g_first_addr == NULL)
		return (malloc(size));
	current_block = (t_block*)(ptr - sizeof(t_block));
	if (check_block_exist(current_block) == FALSE)
		return (NULL);
	if (current_block->is_free == TRUE)
		return (NULL);
	current_zone = (t_zone*)current_block->zone;
	if (right_type_zone(current_zone, size) == TRUE)
		new_block = resize_allocation(current_block, size);
	else
		new_block = new_allocation(current_block, size);
	if (new_block == NULL)
		return (NULL);
	return (new_block->ptr_data);
}
