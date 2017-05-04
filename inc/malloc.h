#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

// Beginning Remove
# include <stdio.h>
// End Remove

# define FALSE 0
# define TRUE 1

# define TINY "T"
# define SMALL "S"
# define LARGE "L"

# define LIMIT_TINY 1000
# define LIMIT_SMALL 10000

# define TINY_BLOCK 100
# define SMALL_BLOCK 1000

# define MIN_ALLOCATION_PER_ZONE 1

void *first_addr;

typedef struct s_block {
	void					*prev_addr;
	void					*next_addr;
	unsigned int	used;
	// char					type;
	size_t				size_data;
	size_t				size_block;
	void					*ptr_data;
} t_block;

// struct page_table = {
// 	void *first_addr;
// 	void *next_page;
// 	char page_type;
// }

/**
 * malloc.c file
 */
void *get_new_zone(size_t size);
void *ft_malloc(size_t size);

/**
* zone.c file
*/

void		*create_empty_zone(size_t block_size);
size_t	get_allocation_size(size_t block_size);
size_t	get_number_of_pages(size_t page_size, size_t block_size);
void		*allocate_zone(size_t allocation_size);
void		init_zone(void *first_zone_addr, size_t allocation_size, size_t block_size);
t_block	*init_one_block(void *block_ptr, size_t size_data);
t_block	*create_outside_zone(size_t size_block);

#endif
