#include "ft_malloc.h"
#include <stdio.h>

void	ft_defragment(unsigned long **map)
{
	unsigned long	*block_state;
	unsigned long	*next_block_state;
	unsigned long	*block_size;

	block_state = *map + 4;
	while (*block_state != TAIL)
	{
		next_block_state = block_state + 3;
		block_size = block_state - 1;
		if (*block_state == FREE && ((*next_block_state == FREE) ||
				(*next_block_state == TAIL)))
		{
			*block_state = *next_block_state;
			*block_size += *(block_size + 3);
			if (*next_block_state == FREE)
				ft_memmove((void*)(block_size + 3), (void*)(block_size + 6), \
							(size_t)(*(*map + 1) - ((block_size + 6) - *map)));
		}
		else
			block_state = next_block_state;
	}
}
