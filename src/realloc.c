/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:05:39 by rklein            #+#    #+#             */
/*   Updated: 2021/11/05 15:04:13 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_copy_from_swap(void *ptr, unsigned long **swap)
{
	ft_memcpy(ptr, (void *)(*swap + 2), *(*swap + 1));
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
	ft_memcpy((void *)(*swap + 2), (void *)*meta, *(meta - 2));
}

void	*ft_find_free_alloc(void *ptr, size_t size)
{
	unsigned long	*map;
	unsigned long	*meta;
	unsigned long	*swap;	

	map = ft_find_map(ptr);
	if (map)
	{
		meta = ft_valid_ptr(&map, ptr);
		if (meta)
		{
			ft_copy_to_swap(meta, &swap);
			ft_free_block(meta);
			ft_defragment(&map);
			ptr = ft_alloc(size);
			if (*(map + 4) == TAIL)
				ft_free_map(*map);
			ft_copy_from_swap(ptr, &swap);
			return (ptr);
		}
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	ptr = ft_find_free_alloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
