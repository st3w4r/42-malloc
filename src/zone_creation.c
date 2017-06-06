/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:38 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:40 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Get a initialized typed zone
*/

t_zone	*get_new_zone(size_t size)
{
	t_zone *zone_ptr;

	if (size <= TINY_BLOCK)
		zone_ptr = create_empty_zone(TINY_BLOCK, TINY);
	else if (size <= SMALL_BLOCK)
		zone_ptr = create_empty_zone(SMALL_BLOCK, SMALL);
	else
		zone_ptr = create_empty_zone(size, LARGE);
	return (zone_ptr);
}

/*
** Create an empty zone and return a pointer on it
** @parm size_t block_size	Get the max size of a block
** @return pointer on the empty zone with header
*/

t_zone	*create_empty_zone(size_t block_size, char type)
{
	size_t	allocation_size;
	void	*ptr_zone;

	if (type == LARGE)
	{
		allocation_size = block_size + sizeof(t_block);
	}
	else
	{
		allocation_size = get_allocation_size(block_size);
	}
	ptr_zone = allocate_zone(allocation_size);
	if (ptr_zone != NULL)
	{
		init_zone(ptr_zone, allocation_size, type);
	}
	return (ptr_zone);
}

size_t	get_allocation_size(size_t block_size)
{
	size_t	nb_page;
	size_t	allocation_size;
	size_t	page_size;

	page_size = getpagesize();
	nb_page = get_number_of_pages(page_size, sizeof(t_block) + block_size);
	allocation_size = nb_page * page_size;
	return (allocation_size);
}

size_t	get_number_of_pages(size_t page_size, size_t block_size)
{
	size_t	nb_page;
	size_t	nb_allocation;

	nb_page = 0;
	nb_allocation = 0;
	if (block_size > 0 && page_size > 0)
	{
		while (nb_allocation < MIN_ALLOCATION_PER_ZONE)
		{
			nb_page++;
			nb_allocation = nb_page * page_size / block_size;
		}
	}
	return (nb_page);
}

void	*allocate_zone(size_t allocation_size)
{
	void *ptr_zone;

	ptr_zone = mmap(0,
									allocation_size,
									PROT_READ | PROT_WRITE,
									MAP_ANON | MAP_PRIVATE,
									-1,
									0);
	if (ptr_zone == MAP_FAILED)
	{
		return (NULL);
	}
	return (ptr_zone);
}
