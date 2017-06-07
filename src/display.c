#include "malloc.h"
// #include <stdio.h>

void display_memory_block(void *addr) {
	t_block *block;
	int i;

	i = 0;
	block = (t_block*)addr;
	if (block != NULL) {

	// while (block != NULL) {
	ft_putstr("---Memory Block---\n");
	ft_putstr("current_addr:"); ft_puthexa((uint64_t)block); ft_putstr("\n");
	ft_putstr("next_addr:"); ft_puthexa((uint64_t)block->next_addr); ft_putstr("\n");
	ft_putstr("is_free:"); ft_putnbr(block->is_free);	ft_putstr("\n");
	ft_putstr("size_data:"); ft_putnbr(block->size_data); ft_putstr("\n");
	// ft_putstr("size_block: %lu\n", block->size_block);
	ft_putstr("ptr_data:"); ft_puthexa((uint64_t)block->ptr_data); ft_putstr("\n");
	ft_putstr("end block:"); ft_puthexa((uint64_t)block->ptr_data + block->size_data); ft_putstr("\n");
	ft_putstr("Counter:"); ft_putnbr(i); ft_putstr("\n");
} else {
	ft_putstr("BLOCK NULL\n");
}
// ft_putstr("\n");
		// block = block->next_addr;
	// }
}

void display_memory_list(t_zone *zone) {
	t_block *block;

	int i;

	i = 0;
	block = (t_block*)zone->first_block;
	ft_putstr("__________Memory List___________\n");
	while (block != NULL) {
		display_memory_block(block);
		ft_putnbr(i);
		ft_putstr("\n");
		block = block->next_addr;
		i++;
	}
}

void display_zone_list(t_zone *zone) {
	t_zone *current_zone;
	int i;

	i = 0;
	current_zone = zone;
	while (current_zone != NULL) {
		// printf("Zone: %i Type: %c Size: %zu Addr: %p MaxAddr: %p\n", i, current_zone->type, current_zone->size, current_zone, current_zone->current_zone + current_zone->size);
		ft_putstr("---Zone list---\n");
		ft_putstr("Zone:"); ft_putnbr(i); ft_putstr(" ");
		ft_putstr("Type:"); ft_putchar(current_zone->type); ft_putstr(" ");
		ft_putstr("Size:"); ft_putnbr(current_zone->size); ft_putstr(" ");
		ft_putstr("Addr:"); ft_puthexa((uint64_t)current_zone); ft_putstr(" ");
		ft_putstr("MaxAddr:"); ft_puthexa((uint64_t)current_zone->current_zone + current_zone->size); ft_putstr(" ");
		ft_putstr("\n");
		i++;
		current_zone = current_zone->next_zone;
	}
	ft_putstr("\n");
}
