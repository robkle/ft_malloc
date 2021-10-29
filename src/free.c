/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:04:18 by rklein            #+#    #+#             */
/*   Updated: 2021/10/25 16:14:18 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_free_block(unsigned long	*ptr)
{
	unsigned long	*block_size;
	unsigned long	*block_state;

	block_size = ptr - 2;
	block_state = ptr - 1;
	*block_state = FREE;
	*block_size = (*block_size + 31) & -32;
	ft_memset((void *)*ptr, 0, *block_size);
}

void	free(void *ptr)
{
	unsigned long	*map;
	unsigned long	*meta;

	if (!ptr)
		return ;
	//mutex
	map = ft_find_map(ptr);
	if (map)
	{
		meta = ft_valid_ptr(&map, ptr);
		if (meta)
		{
			ft_free_block(meta);
			ft_defragment(&map);
			if (*(map + 4) == TAIL)
				ft_free_map(*map);
		}
	}
	//mutex
}
