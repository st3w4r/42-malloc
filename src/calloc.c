#include "malloc.h"

extern void		*calloc(size_t count, size_t size)
{
  char *ptr;
  size_t allocation_size;

  ptr = NULL;
  allocation_size = count * size;
  ptr = malloc(allocation_size);
  if (ptr != NULL)
    ft_bzero(ptr, allocation_size);
  return ptr;
}
