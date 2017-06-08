/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:21:02 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/05 15:21:03 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern void	free(void *ptr)
{
	t_block	*block;
	t_zone	*zone;

	if (ptr != NULL && g_first_addr != NULL)
	{
		block = (t_block*)(ptr - sizeof(t_block));
		if (check_block_exist(block) == TRUE)
		{
			if (block->is_free == TRUE)
				return ;
			zone = (t_zone*)block->zone;
			release_block(block);
			release_empty_zone(zone);
		}
	}
}
