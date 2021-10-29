/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:04:39 by rklein            #+#    #+#             */
/*   Updated: 2021/10/29 14:26:11 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_insert_block(unsigned long **mem, unsigned long **block, \
			size_t size)
{
	void	*ptr;
	size_t	alloc_size;

	if (**block == alloc_size)
	{
		**block = size;
		*(*block + 1) = INUSE;
		ptr = (void *)*(*block + 2);
	}
	else if (**block > alloc_size)
	{
		ft_memmove((void *)(*block + 3), (void *)*block, \
			(size_t)(*(*mem + 1) - ((*block + 3) - *mem)));
		**block = size;
		*(*block + 1) = INUSE;
		*(*block + 2) = *(*block + 5);
		*(*block + 3) -= alloc_size;
		*(*block + 4) = FREE;
		*(*block + 5) += alloc_size;
		ptr = (void *)*(*block + 2);
	}
	return (ptr);
}

void	*ft_append_block(unsigned long **block, size_t size)
{
	size_t	alloc_size;

	alloc_size = (size + 31) & -32;
	*(*block + 3) = **block - alloc_size;
	*(*block + 4) = TAIL;
	*(*block + 5) = *(*block + 2) + alloc_size;
	**block = size;
	*(*block + 1) = INUSE;
	return ((void *)*(*block + 2));
}

void	*ft_add_block(unsigned long **mem, size_t size, size_t map_size)
{
	unsigned long	*block;
	unsigned long 	*current;
	
	block = *mem + 3;
	current = *mem;
	while (current)
	{
		if (*(block + 1) == FREE && ((size + 31) & -32) <= *block)
			return (ft_insert_block(mem, &block, size));
		if (*(block + 1) == TAIL && ((size + 31) & -32) < *block)
			return (ft_append_block(&block, size));
		if (*(block + 1) == TAIL && ((size + 31) & -32) >= *block)
		{
			if (*(current + 2))
			{
				current = (unsigned long *)*(current + 2);
				block = current + 3;
			}
			else
				return (ft_append_page(&current, map_size, size));
		}
		else
			block = block + 3;
	}
	return (NULL);
}

void	ft_get_zone(size_t size, size_t *map_size, unsigned long ***mem)
{
	size_t	alloc_size;

	alloc_size = (size + 31) & -32;
	if (alloc_size <= TINY)
	{
		*mem = &g_zone.tiny;
		*map_size = N;
	}
	else if (alloc_size <= SMALL)
	{
		*mem = &g_zone.small;
		*map_size = M;
	}
	else
	{
		*mem = &g_zone.large;
		*map_size = (alloc_size + 128 + (PAGE - 1)) & -PAGE;
	}
}

void	*malloc(size_t size)
{
	unsigned long	**mem;
	size_t			map_size;
	void			*ptr;

	if (ft_size_limit(size) == 0)
		return (NULL);
	ft_get_zone(size, &map_size, &mem);
	if (!(*mem))
		ft_initiate_page(mem, map_size); //try *mem
	ptr = ft_add_block(mem, size, map_size);
	return (ptr);
	
}
