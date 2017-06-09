# Malloc

Memory allocator

3 type of zone:

- TINY
- SMALL
- LARGE

## Build  

	make
	cc ./test/test1.c -o test1

## Test

Replace the dynamic library malloc by yours:

	./test/run.sh <test_program>
