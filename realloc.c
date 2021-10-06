#include "ft_malloc.h"

void	ft_copy_from_swap(void *ptr, unsigned long **swap)
{
	ft_memcpy(ptr, (void*)(*swap + 2), *(*swap + 1));
	munmap(*swap, **swap);
	*swap = NULL;
}

void	ft_copy_to_swap(unsigned long *meta, unsigned long **swap)
{
	unsigned long	map_size;
	
	map_size = (*(meta - 2) + 16 + (PAGE - 1)) & -PAGE;
	*swap = mmap(NULL, map_size, PROT_READ | PROT_WRITE, \
		MAP_ANON | MAP_PRIVATE, -1, 0);
	**swap = map_size;
	*(*swap + 1) = *(meta - 2);
	ft_memcpy((void*)(*swap + 2), (void*)*meta, *(meta - 2));
}

void	*ft_realloc(void *ptr, size_t size)
{
	unsigned long	*map;
	unsigned long	*meta;
	unsigned long	*swap;	
	
	if (ptr == NULL)
		return (ft_malloc(size));
	if (map = ft_find_map(ptr))
	{
		if ((meta = ft_valid_ptr(&map, ptr)))
		{
			ft_copy_to_swap(meta, &swap);
			ft_free_block(meta);
			ft_defragment(&map);
			ptr = ft_malloc(size);
			if (*(map + 4) == TAIL)
				ft_free_map(*map);
			ft_copy_from_swap(ptr, &swap);
			return (ptr);
		}
	}
	return (NULL);
}
