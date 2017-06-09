/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:24:59 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/07 15:17:33 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdint.h>

# define FALSE 0
# define TRUE 1

# define TINY 'T'
# define SMALL 'S'
# define LARGE 'L'

# define TINY_BLOCK 1024
# define SMALL_BLOCK 1024 * 32

# define MIN_ALLOCATION_PER_ZONE 100

typedef struct	s_block {
	void			*zone;
	void			*next_addr;
	size_t			size_data;
	unsigned int	is_free;
	void			*ptr_data;
}				t_block;

typedef struct	s_zone {
	t_block		*first_block;
	void		*current_zone;
	void		*next_zone;
	void		*previous_zone;
	size_t		size;
	char		type;
}				t_zone;

typedef unsigned int	t_bool;

void			*g_first_addr;

/*
** File: show_alloc_mem.c
*/
extern void		show_alloc_mem();

/*
** File: realloc.c
*/
extern void		*realloc(void *ptr, size_t size);

/*
** File: realloc.c
*/
extern void		*reallocf(void *ptr, size_t size);

/*
** File: calloc.c
*/
extern void		*calloc(size_t count, size_t size);

/*
** File: malloc.c
*/
extern void		*malloc(size_t size);

/*
** File: free.c
*/
extern void		free(void *ptr);

/*
** File: zone_creation.c
*/
t_zone			*get_new_zone(size_t size);
t_zone			*create_empty_zone(size_t block_size, char type);
size_t			get_allocation_size(size_t block_size);
size_t			get_number_of_pages(size_t page_size, size_t block_size);
void			*allocate_zone(size_t allocation_size);

/*
** File: zone_initialisation.c
*/
void			init_zone(void *first_zone_addr,
						size_t allocation_size, char type);
t_zone			*add_new_zone(t_zone *zone, size_t size_data);
t_zone			*get_right_zone(t_zone *first_zone, size_t size_data);
t_bool			right_type_zone(t_zone *zone, size_t size_data);
t_bool			is_space_available_zone(t_zone *zone, size_t size_data_block);

/*
** File: zone_deletion.c
*/
t_bool			zone_is_empty(t_zone *zone);
void			release_zone(t_zone *zone);
void			release_empty_zone(t_zone *current_zone);

/*
** File: block_initialisation.c.
*/

t_block			*init_one_block(t_zone *zone, void *block_ptr,
								size_t size_data);
void			set_block_to_used(t_block *block, size_t size_data);
void			release_block(t_block *block);
t_bool			check_block_exist(t_block *addr_block);

/*
** File: block_creation.c.
*/
t_bool			is_space_available_block(t_block *block, size_t size_data);
t_block			*get_last_block(t_zone *zone);
t_block			*get_block_unused(t_block *block);
t_block			*get_reusable_block(t_block *block, size_t size_data);
t_block			*add_block_to_zone(t_zone *zone, size_t size_data);

/*
** File: libft
*/
void			ft_puthexa(uint64_t nb);
void			ft_putnbr(int n);
void			ft_putstr(char const *s);
void			ft_putchar(char c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);

#endif
