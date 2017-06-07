/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:20:55 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 17:05:22 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*init_one_block(t_zone *zone, void *block_ptr, size_t size_data)
{
	t_block	*block;

	block = (t_block*)block_ptr;
	block->zone = zone;
	block->next_addr = NULL;
	block->is_free = TRUE;
	block->size_data = size_data;
	block->ptr_data = block_ptr + sizeof(t_block);
	return (block);
}

void	set_block_to_used(t_block *block, size_t size_data)
{
	block->size_data = size_data;
	block->is_free = FALSE;
}

void	release_block(t_block *block)
{
	block->is_free = TRUE;
}

t_bool	check_block_exist(t_block *addr_block)
{
	t_zone	*current_zone;
	t_block	*current_block;
	t_bool	is_exist;

	is_exist = FALSE;
	current_zone = (t_zone *)g_first_addr;
	while (current_zone != NULL)
	{
		current_block = current_zone->first_block;
		while (current_block != NULL)
		{
			if (current_block == addr_block)
			{
				is_exist = TRUE;
			}
			current_block = (t_block*)current_block->next_addr;
		}
		current_zone = (t_zone*)current_zone->next_zone;
	}
	return (is_exist);
}
