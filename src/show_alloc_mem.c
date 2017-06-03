/*
  TINY : 0xA0000
  0xA0020 - 0xA004A : 42 octets
  0xA006A - 0xA00BE : 84 octets
  SMALL : 0xAD000
  0xAD020 - 0xADEAD : 3725 octets
  LARGE : 0xB0000
  0xB0020 - 0xBBEEF : 48847 octets
  Total : 52698 octets
*/

#include "malloc.h"

void ft_puthexa(uint64_t nb) {
  char hex_revert[16];
  int hex[16];
  int i;

  ft_bzero(hex_revert, 16);
  ft_bzero(hex, 16);
  i = 0;
  while (nb) {
    hex[i] = nb % 16;
    if (hex[i] >= 10) {
      hex_revert[i] = hex[i] + 'A' - 10;
    } else {
      hex_revert[i] = hex[i] + '0';
    }
    nb /= 16;
    i++;
  }
  ft_putstr("0x");
  while (i >= 0) {
    ft_putchar(hex_revert[i]);
    i--;
  }
}

void display_addr(void *addr) {
  ft_puthexa((uint64_t)addr);
  ft_putchar('\n');
  // printf("%d\n", convert_addr);
  // printf("0x%X\n", convert_addr);
  // printf("%p\n", addr);
  // ft_putnbr(str_addr[0]);
}

void display_octets(t_block *block) {
  size_t size;

  size = block->size_data;
  ft_putnbr(size);
  ft_putstr(" octets");
}

void show_memory_block(void *addr) {
	t_block *block;

	block = (t_block*)addr;
	while (block != NULL) {
    ft_puthexa((uint64_t)block->ptr_data);
    ft_putstr(" - ");
    ft_puthexa((uint64_t)block->ptr_data + (uint64_t)block->size_data);
    ft_putstr(" : ");
    display_octets(block);
    ft_putchar('\n');
		block = block->next_addr;
	}
}

void show_memory_zone(t_zone *zone) {
	t_zone *current_zone;
	t_block *block;

	current_zone = zone;
  while (current_zone != NULL && current_zone->next_zone != NULL) {
    current_zone = current_zone->next_zone;
  }

	while (current_zone != NULL) {
    if (current_zone->type == 'T') {
      ft_putstr("TINY : ");
    } else if (current_zone->type == 'S') {
      ft_putstr("SMALL : ");
    } else {
      ft_putstr("LARGE : ");
    }
    display_addr(current_zone->current_zone);
    show_memory_block(current_zone->first_block);
		current_zone = current_zone->previous_zone;
	}
}

void show_total(t_zone *zone) {
  u_int total;
  t_zone *current_zone;
	t_block *block;

  current_zone = zone;
  while (current_zone != NULL) {
    block = current_zone->first_block;
    while (block != NULL) {
      total += block->size_data;
      block = block->next_addr;
    }
    current_zone = current_zone->next_zone;
  }
  ft_putstr("Total : ");
  ft_putnbr(total);
  ft_putstr(" octets\n");
}

void show_alloc_mem() {
  t_zone *zone;

  zone = (t_zone*)first_addr;
  show_memory_zone(zone);
  show_total(zone);
}
