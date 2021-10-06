#include "ft_malloc.h"
#include <stdio.h>

void	ft_initiate_page(unsigned long **mem, size_t map_size)//SAFE VERSION
{
	*mem = mmap(NULL, map_size, PROT_READ | PROT_WRITE, \
		MAP_ANON | MAP_PRIVATE, -1, 0);
	**mem = map_size;
	if (map_size == N)
		*(*mem + 1) = (unsigned long)32768;
	else if (map_size == M)
		*(*mem + 1) = (unsigned long)49152;
	else
		*(*mem + 1) = (unsigned long)128;
	*(*mem + 2) = (unsigned long)0x0;
	*(*mem + 3) = (unsigned long)(map_size - (*(*mem + 1)));
	*(*mem + 4) = (unsigned long)TAIL;
	*(*mem + 5) = (unsigned long)*mem + *(*mem + 1);
	/*printf("map size: %lu\n", **mem);
	printf("meta size: %lu\n", *(*mem + 1));
	printf("block size: %lu\n", *(*mem + 3));
	printf("block ptr: %#lx\n", *(*mem + 5));
	printf("size check: %lu\n",*(*mem + 5) - (unsigned long)*mem);*/
}

void	ft_append_page(unsigned long **mem, size_t map_size)//SAFE VERSION
{
	unsigned long	*new;
	
	ft_initiate_page(&new, map_size);
	*(*mem + 2) = (unsigned long)new;
}
