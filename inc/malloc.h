#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>

// Beginning Remove
# include <stdio.h>
// End Remove

# define FALSE 0
# define TRUE 1

# define TINY 'T'
# define SMALL 'S'
# define LARGE 'L'

# define LIMIT_TINY 1000
# define LIMIT_SMALL 10000

# define TINY_BLOCK 1000
# define SMALL_BLOCK 10000

# define MIN_ALLOCATION_PER_ZONE 100

typedef struct s_block {
	void					*zone;
	void					*current_addr;
	void					*next_addr;
	size_t				size_data;
	unsigned int	is_free;
	void					*ptr_data;
} t_block;

typedef struct s_zone {
	t_block	*first_block;
	void		*current_zone;
	void		*next_zone;
	size_t	size;
	char		type;
} t_zone;

typedef unsigned int t_bool;

void *first_addr;

/**
* File: show_alloc_mem.c
*/

void	show_alloc_mem();

/**
* File: realloc.c
*/
void	*ft_realloc(void *ptr, size_t size);

/**
 * File: malloc.c
 */
void *ft_malloc(size_t size);

/**
 * File: free.c
 */
void ft_free(void *ptr);


/**
* File: zone.c
*/
t_zone	*get_new_zone(size_t size);
t_zone	*create_empty_zone(size_t block_size, char type);
size_t	get_allocation_size(size_t block_size);
size_t	get_number_of_pages(size_t page_size, size_t block_size);
void		*allocate_zone(size_t allocation_size);
void		init_zone(void *first_zone_addr, size_t allocation_size, size_t block_size, char type);
t_bool	is_space_available_zone(t_zone *zone, size_t size_data_block);
t_zone	*add_new_zone(t_zone *zone, size_t size_data);
t_bool right_type_zone(t_zone *zone, size_t size_data);
t_bool zone_is_empty(t_zone *zone);
void release_zone(t_zone *zone);
void release_empty_zone(t_zone *first_zone);

// t_block	*create_self_zone(size_t size_block);

/**
* File: block.c.
*/

t_block	*init_one_block(t_zone *zone, void *block_ptr, size_t size_data);
void		set_block_to_used(t_block *block, size_t size_data);
t_block *get_last_block(t_zone *zone);
// t_block	*add_new_block(t_zone *zone, t_block *block);
t_block	*get_block_unused(t_block *block);
t_bool	is_space_available_block(t_block *block, size_t size_data);
// t_block *get_block_unused_size(t_block *block, size_t size_data);
t_block *get_reusable_block(t_block *block, size_t size_data);
void release_block(t_block *block);

#endif
