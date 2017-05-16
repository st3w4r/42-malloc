#include "malloc.h"

void ft_free(void *ptr) {
  if (ptr != NULL) {
    realease_block(ptr);
  }
}
