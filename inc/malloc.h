#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>

# define TINY "T"
# define SMALL "S"
# define LARGE "L"

# define LIMIT_TINY 1000
# define LIMIT_SMALL 10000

# define TINY_ZONE 1024
# define SMALL_ZONE 10000

void *page_table;

struct page_table = {
	void *first_addr;
	void *next_page;
	char page_type;
}

/**
 * malloc.c file
 */
void *malloc(size_t size);

#endif
