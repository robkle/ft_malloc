/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:51:10 by rklein            #+#    #+#             */
/*   Updated: 2021/10/15 13:59:08 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	ft_size_limit(size_t size)
{
	struct rlimit	limit;

	if (size <= 0)
		return (0);
	getrlimit(RLIMIT_AS, &limit);
	if (((((size + 31) & -32) + 128 + (PAGE - 1)) & -PAGE) > limit.rlim_cur)
		return (0);
	return (1);
}
