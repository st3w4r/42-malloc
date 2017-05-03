#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdint.h>

/*
int main(int argc, char **argv) {

	int i;
	int nb;
	char c;
	char *str;
	int page_size;

	nb = atoi(argv[2]);
	c = argv[1][0];
	str = (char*)mmap(0, nb + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	i = 0;

	while(i<nb) {
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);
	page_size = getpagesize();
	printf("%d\n", page_size);

	int success;
	struct rlimit *rlimit;

	rlimit = malloc(sizeof(struct rlimit));

	// printf("Limit: %lu\n", sizeof(struct rlimit));

	success = getrlimit(RLIMIT_NPROC, rlimit);

	printf("Core limit soft: %ju\n", (uintmax_t)rlimit->rlim_cur);
	printf("Core limit soft: %juMB\n", (uintmax_t)rlimit->rlim_cur / 1024 / 1024);
	printf("Core limit hard: %ju\n", (uintmax_t)rlimit->rlim_max);

	return (0);
}
*/

void ft_get_page(size_t size) {	
	void *first_addr;
	int page_numbers;
	int page_size;

	page_size = getpagesize();

	if (page_size > 0)
	{	

	page_number = size / getpagesize();

	if (size > LIMIT_TINY)
	{
		
	}
	
	first_addr = mmap(0, , 

	}
}

int main(int argc, char **) {

	first_addr = mmap(0, LIMI
}
// void *malloc(size_t size) {
//
// }
//
// void free(void *ptr) {
//
// }
//
// void *realloc(void *ptr, size_t size) {
//
// }
