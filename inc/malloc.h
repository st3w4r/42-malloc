#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

// Beginning Remove
# include <stdio.h>
// End Remove

# define TINY "T"
# define SMALL "S"
# define LARGE "L"

# define LIMIT_TINY 1000
# define LIMIT_SMALL 10000

# define TINY_BLOCK 10
# define SMALL_BLOCK 10000

# define MIN_ALLOCATION_PER_ZONE 100

void *first_addr;

typedef struct s_block {
	void					*first_addr;
	void					*next_addr;
	unsigned int	used;
	char					type;
	size_t				size_data;
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
void *malloc(size_t size);

/**
* zone.c file
*/

void		*create_empty_zone(size_t block_size);
size_t	get_number_of_pages(size_t page_size, size_t block_size);


#endif
