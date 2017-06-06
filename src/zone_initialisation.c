/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:58 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:59 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Add the header to the zone
*/

void	init_zone(void *first_zone_addr, size_t allocation_size, char type)
{
	t_zone	*zone;

	zone = (t_zone*)first_zone_addr;
	zone->first_block = first_zone_addr + sizeof(t_zone);
	zone->current_zone = first_zone_addr;
	zone->next_zone = NULL;
	zone->previous_zone = NULL;
	zone->size = allocation_size;
	zone->type = type;
}

/*
** Add a new zone as next zone, return the new zone or NULL
*/

t_zone	*add_new_zone(t_zone *zone, size_t size_data)
{
	t_zone *current_zone;
	t_zone *next_zone;

	if (zone == NULL)
	{
		return (NULL);
	}
	current_zone = zone;
	while (current_zone->next_zone != NULL)
	{
		current_zone = current_zone->next_zone;
	}
	current_zone->next_zone = get_new_zone(size_data);
	if (current_zone->next_zone != NULL)
	{
		next_zone = current_zone->next_zone;
		next_zone->previous_zone = current_zone;
	}
	return (current_zone->next_zone);
}

/*
** Retrun the right zone or return null no zone available
*/

t_zone	*get_right_zone(t_zone *first_zone, size_t size_data)
{
	t_zone *current_zone;

	current_zone = first_zone;
	while (current_zone != NULL)
	{
		if (right_type_zone(current_zone, size_data) == TRUE)
		{
			return (current_zone);
		}
		current_zone = current_zone->next_zone;
	}
	return (current_zone);
}

/*
** Send data size and a zone, return True if the zone can get this size of data
*/

t_bool	right_type_zone(t_zone *zone, size_t size_data)
{
	t_bool	result;

	result = FALSE;
	if (zone && zone->type)
	{
		if (zone->type == 'T' && size_data <= TINY_BLOCK)
			result = TRUE;
		else if (zone->type == 'S'
						&& size_data > TINY_BLOCK
						&& size_data <= SMALL_BLOCK)
			result = TRUE;
		else if (zone->type == 'L' && size_data > SMALL_BLOCK)
			result = TRUE;
		else
			result = FALSE;
	}
	return (result);
}

t_bool	is_space_available_zone(t_zone *zone, size_t size_data_block)
{
	t_block	*last_block;
	void	*max_addr;
	void	*next_addr;

	last_block = get_last_block(zone);
	max_addr = zone->current_zone + zone->size;
	next_addr = (void*)last_block + sizeof(t_block)
							+ last_block->size_data + sizeof(t_block)
							+ size_data_block;
	if (next_addr > max_addr)
	{
		return (FALSE);
	}
	return (TRUE);
}
