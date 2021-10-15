/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:05:03 by rklein            #+#    #+#             */
/*   Updated: 2021/10/15 10:17:12 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_initiate_page(unsigned long **mem, size_t map_size)
{
	*mem = mmap(NULL, map_size, PROT_READ | PROT_WRITE, \
		MAP_ANON | MAP_PRIVATE, -1, 0);
	**mem = map_size;
	if (map_size == N)
		*(*mem + 1) = (unsigned long)32768;
	else if (map_size == M)
		*(*mem + 1) = (unsigned long)49152;
	else
		*(*mem + 1) = (unsigned long)128;
	*(*mem + 2) = (unsigned long)0x0;
	*(*mem + 3) = (unsigned long)(map_size - (*(*mem + 1)));
	*(*mem + 4) = (unsigned long)TAIL;
	*(*mem + 5) = (unsigned long)*mem + *(*mem + 1);
}

void	ft_append_page(unsigned long **mem, size_t map_size)
{
	unsigned long	*new;

	ft_initiate_page(&new, map_size);
	*(*mem + 2) = (unsigned long)new;
}
