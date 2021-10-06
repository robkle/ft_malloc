#include "ft_malloc.h"

unsigned long	*ft_valid_ptr(unsigned long **map, void *ptr)
{
	unsigned long	*block_ptr;
	unsigned long	*block_state;

	block_ptr = *map + 5;
	block_state = *map + 4;

	while ((void*)(*block_ptr) <= ptr && *block_state != TAIL)
	{
		if (ptr == (void*)(*block_ptr))
			return (block_ptr);

		block_ptr += 3;
		block_state += 3;
	}
	return (NULL);
}

unsigned long	*ft_scan_map(unsigned long **zone, void *ptr)
{
	unsigned long	*current;
	
	if (*zone)
	{
		current = *zone;
		while (current)
		{
			if (ptr >= (void*)current + *(current + 1) && \
				ptr < (void*)current + *current)
				return (current);
			current = (unsigned long*)*(current + 2);
		}
	}
	return (NULL);	
}

unsigned long	*ft_find_map(void *ptr)
{
	unsigned long	*map;
	
	if (!(map = ft_scan_map(&g_zone.tiny, ptr)))
	{
		if(!(map = ft_scan_map(&g_zone.small, ptr)))
			map = ft_scan_map(&g_zone.large, ptr);
	}
	return (map);
}

