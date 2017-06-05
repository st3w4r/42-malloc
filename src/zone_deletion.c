/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_deletion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:47 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:48 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Return TRUE if all block is free in the zone or false if not
*/

t_bool	zone_is_empty(t_zone *zone)
{
	t_block *block;

	block = zone->first_block;
	while (block != NULL)
	{
		if (block->is_free == FALSE)
		{
			return (FALSE);
		}
		block = block->next_addr;
	}
	return (TRUE);
}

void	release_zone(t_zone *zone)
{
	int result;

	result = munmap(zone->current_zone, zone->size);
}

void	release_empty_zone(t_zone *first_zone)
{
	t_zone *current_zone;
	t_zone *previous_zone;
	t_zone *next_zone;

	current_zone = first_zone;
	previous_zone = NULL;
	next_zone = NULL;
	while (current_zone != NULL)
	{
		next_zone = current_zone->next_zone;
		if (zone_is_empty(current_zone) == TRUE)
		{
			release_zone(current_zone);
			if (previous_zone == NULL)
				g_first_addr = next_zone;
			else
				previous_zone->next_zone = next_zone;
		}
		else
		{
			previous_zone = current_zone;
		}
		current_zone = next_zone;
	}
}
