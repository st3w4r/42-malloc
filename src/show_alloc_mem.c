/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:32 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:34 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	display_octets(t_block *block)
{
	size_t size;

	size = block->size_data;
	ft_putnbr(size);
	ft_putstr(" octets");
}

void	show_memory_block(void *addr)
{
	t_block *block;

	block = (t_block*)addr;
	while (block != NULL)
	{
		ft_puthexa((uint64_t)block->ptr_data);
		ft_putstr(" - ");
		ft_puthexa((uint64_t)block->ptr_data + (uint64_t)block->size_data);
		ft_putstr(" : ");
		display_octets(block);
		ft_putchar('\n');
		block = block->next_addr;
	}
}

void	show_memory_zone(t_zone *zone)
{
	t_zone	*current_zone;

	current_zone = zone;
	while (current_zone != NULL)
	{
		if (current_zone->type == 'T')
			ft_putstr("TINY : ");
		else if (current_zone->type == 'S')
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_puthexa((uint64_t)current_zone->current_zone);
		ft_putchar('\n');
		show_memory_block(current_zone->first_block);
		current_zone = current_zone->next_zone;
	}
}

void	show_total(t_zone *zone)
{
	uint64_t	total;
	t_zone		*current_zone;
	t_block		*block;

	total = 0;
	current_zone = zone;
	while (current_zone != NULL)
	{
		block = current_zone->first_block;
		while (block != NULL)
		{
			total += block->size_data;
			block = block->next_addr;
		}
		current_zone = current_zone->next_zone;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}

void	show_alloc_mem(void)
{
	t_zone *zone;

	zone = (t_zone*)g_first_addr;
	show_memory_zone(zone);
	show_total(zone);
}
