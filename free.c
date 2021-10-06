#include "ft_malloc.h"

void	ft_free_block(unsigned long	*ptr)
{
	unsigned long	*block_size;
	unsigned long	*block_state;

	block_size = ptr - 2;
	block_state = ptr - 1;
	*block_state = FREE;
	*block_size = (*block_size + 31) & -32; //REAL SIZE
	ft_memset((void*)*ptr, 0, *block_size);
}

void	ft_free(void *ptr)
{
	unsigned long	*map;
	unsigned long	*meta;

	if (!ptr)
		return;
	if ((map = ft_find_map(ptr)))
	{
		if ((meta = ft_valid_ptr(&map, ptr)))
		{
			ft_free_block(meta);
			ft_defragment(&map);
			if (*(map + 4) == TAIL)
				ft_free_map(*map);
		}
	}
}
