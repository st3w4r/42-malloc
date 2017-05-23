#include "malloc.h"

void ft_free(void *ptr) {
  if (ptr != NULL) {
    release_block(ptr);
    release_empty_zone((t_zone *)first_addr);
  }
}
