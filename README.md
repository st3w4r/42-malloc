# Malloc

Memory allocator, is a shared library `libft_malloc.so`

## Exposed Functions

	void *malloc(size_t size);
	void free(void *ptr);
	void *realloc(void *ptr, size_t size);
	void *calloc(size_t count, size_t size);

## Arch

3 type of zone:

- TINY
- SMALL
- LARGE

## Build  

	make
	cc ./test/test1.c -o test1

## Test

Replace the system dynamic library malloc by yours:

	./test/run.sh <test_program>
