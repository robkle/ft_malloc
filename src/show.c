/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:05:49 by rklein            #+#    #+#             */
/*   Updated: 2021/10/15 13:30:23 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_alloc_mem(char *zone, unsigned long *mem, size_t *total)
{
	unsigned long	*current;
	unsigned long	*block;

	if (!mem)
		return ;
	current = mem;
	while (current)
	{
		ft_printf("%s : %#lx\n", zone, (unsigned long)current + *(current + 1));
		block = current + 3;
		while (*(block + 1) != TAIL)
		{
			if (*(block + 1) == INUSE)
			{
				ft_printf("%#lx - %#lx : %lu bytes\n", \
						*(block + 2), *(block + 2) + *block, *block);
				*total += *block;
			}
			block += 3;
		}
		current = (unsigned long *)*(current + 2);
	}
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	print_alloc_mem("TINY", g_zone.tiny, &total);
	print_alloc_mem("SMALL", g_zone.small, &total);
	print_alloc_mem("LARGE", g_zone.large, &total);
	ft_printf("Total : %lu bytes\n", total);
}
