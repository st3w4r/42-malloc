#include "malloc.h"

void ft_free(void *ptr) {
  realease_block(ptr);
}
