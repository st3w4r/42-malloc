#ifndef MALLOC_H
# define MALLOC_H

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

# define TINY_BLOCK 100
# define SMALL_BLOCK 1000

# define MIN_ALLOCATION_PER_ZONE 1

typedef struct s_block {
	void					*current_addr;
	void					*next_addr;
	void					*ptr_data;
	size_t				size_data;
	unsigned int	is_free;
	// char					type;
	// size_t				size_data;
	// size_t				size_block;
} t_block;

typedef struct s_zone {
	t_block		*first_block;
  void		*current_zone;
  void		*next_zone;
	size_t	size;
	char		type;
} t_zone;

typedef unsigned int t_bool;

void *first_addr;


// typedef struct s_zone_table {
//   t_zone *tiny_zone;
//   t_zone *small_zone;
//   t_zone *large_zone;
// } t_zone_table;

// struct page_table = {
// 	void *first_addr;
// 	void *next_page;
// 	char page_type;
// }

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
// t_block	*create_self_zone(size_t size_block);

/**
* File: block.c.
*/

t_block *init_one_block(t_block *block_ptr);
void		set_block_to_used(t_block *block, size_t size_data);
t_block *get_last_block(t_zone *zone);
// t_block	*add_new_block(t_zone *zone, t_block *block);
t_block	*get_block_unused(t_block *block);
void realease_block(t_block *block);

#endif
