/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:23 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:24 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone	*init_first_zone(size_t size_data)
{
	t_zone	*first_zone;

	first_zone = (t_zone*)g_first_addr;
	if (first_zone == NULL)
	{
		first_zone = get_new_zone(size_data);
		if (first_zone == NULL)
			return (NULL);
		g_first_addr = first_zone;
		init_one_block(first_zone, first_zone->first_block, size_data);
	}
	return (first_zone);
}

t_block	*get_block(t_block *block, t_zone *first_zone, size_t size)
{
	t_zone	*current_zone;

	current_zone = first_zone;
	while (block == NULL)
	{
		current_zone = get_right_zone(current_zone, size);
		if (current_zone == NULL)
		{
			current_zone = add_new_zone(first_zone, size);
			if (current_zone == NULL)
				return (NULL);
			init_one_block(current_zone, current_zone->first_block, size);
		}
		block = get_reusable_block(current_zone->first_block, size);
		if (block == NULL)
		{
			if (is_space_available_zone(current_zone, size) == TRUE)
				block = add_block_to_zone(current_zone, size);
			else
				current_zone = current_zone->next_zone;
		}
	}
	return (block);
}

void	*malloc(size_t size)
{
	// void *ptr_zone;
	//
	// ptr_zone = mmap(0,
	// 								size,
	// 								PROT_READ | PROT_WRITE,
	// 								MAP_ANON | MAP_PRIVATE,
	// 								-1,
	// 								0);
	// ft_puthexa((uint64_t)ptr_zone);
	// ft_putstr("\n");
	// return ptr_zone;
	t_zone	*first_zone;
	t_block	*block;

	first_zone = init_first_zone(size);
	if (first_zone == NULL) {
		// ft_putstr("RETURN NULL\n");
		return (NULL);
	}
	block = NULL;
	block = get_block(block, first_zone, size);
	if (block == NULL) {
		// ft_putstr("RETURN NULL\n");
		return (NULL);
	}
	set_block_to_used(block, size);
	//
	// ft_puthexa((uint64_t)block);
	// ft_putstr(" - ");
	// ft_puthexa((uint64_t)block->ptr_data);
	// ft_putstr(" - ");
	// ft_putnbr((uint64_t)block->size_data);
	// ft_putstr("\n");
	// display_memory_list(first_zone);
// display_memory_block(block);
// display_zone_list(first_zone);
	return (block->ptr_data);
}
