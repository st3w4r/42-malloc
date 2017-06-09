#include "malloc.h"
#include <stdio.h>

extern void *reallocf(void *ptr, size_t size)
{
  ptr = realloc(ptr, size);
  if (ptr == NULL)
    free(ptr);
  return ptr;
}
