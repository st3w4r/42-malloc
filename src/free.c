#include "malloc.h"

void ft_free(void *ptr) {
  if (ptr != NULL) {
    release_block((t_block*)(ptr - sizeof(t_block)));
    release_empty_zone((t_zone *)first_addr);
  }
}
