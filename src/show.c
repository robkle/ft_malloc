/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:05:49 by rklein            #+#    #+#             */
/*   Updated: 2021/11/05 14:06:35 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_zone(char *zone, unsigned long *start)
{
	ft_putstr(zone);
	write(1, " : ", 3);
	ft_puthex((unsigned long)start + *(start + 1));
	write(1, "\n", 1);
}

void	print_block(unsigned long *block)
{
	ft_puthex(*(block + 2));
	ft_putstr(" - ");
	ft_puthex(*(block + 2) + *block);
	ft_putstr(" : ");
	ft_putsize(*block);
	ft_putstr(" bytes\n");
}

void	print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putsize(total);
	ft_putstr(" bytes\n");
}

void	print_alloc_mem(char *zone, unsigned long *mem, size_t *total)
{
	unsigned long	*current;
	unsigned long	*block;

	if (!mem)
		return ;
	current = mem;
	while (current)
	{
		print_zone(zone, current);
		block = current + 3;
		while (*(block + 1) != TAIL)
		{
			if (*(block + 1) == INUSE)
			{
				print_block(block);
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

	pthread_mutex_lock(&g_mutex);
	total = 0;
	print_alloc_mem("TINY", g_zone.tiny, &total);
	print_alloc_mem("SMALL", g_zone.small, &total);
	print_alloc_mem("LARGE", g_zone.large, &total);
	print_total(total);
	pthread_mutex_unlock(&g_mutex);
}
