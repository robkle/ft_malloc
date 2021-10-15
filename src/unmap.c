/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:06:56 by rklein            #+#    #+#             */
/*   Updated: 2021/10/15 10:18:52 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_unmap(unsigned long **map)
{
	unsigned long	*current;
	unsigned long	*prev;

	current = *map;
	prev = NULL;
	while (current)
	{
		if (*(current + 4) == TAIL)
		{
			if (prev == NULL)
				*map = (unsigned long *)*(*map + 2);
			else
				*(prev + 2) = *(current + 2);
			munmap(current, *current);
			break ;
		}
		prev = current;
		current = (unsigned long *)*(current + 2);
	}
}

void	ft_free_map(unsigned long map_size)
{
	if (map_size == N)
		ft_unmap(&g_zone.tiny);
	else if (map_size == M)
		ft_unmap(&g_zone.small);
	else
		ft_unmap(&g_zone.large);
}
