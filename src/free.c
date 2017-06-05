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

void ft_free(void *ptr) {
  if (ptr != NULL && first_addr != NULL) {
    release_block((t_block*)(ptr - sizeof(t_block)));
    release_empty_zone((t_zone *)first_addr);
  }
}
