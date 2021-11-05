/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:38:49 by rklein            #+#    #+#             */
/*   Updated: 2021/11/05 14:28:00 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_puthex(unsigned long value)
{
	char			*base_char;
	char			hex[20];
	unsigned long	tmp;
	int				len;

	ft_putstr("0x");
	base_char = "0123456789ABCDEF";
	tmp = value;
	len = 1;
	tmp /= 16;
	while (tmp)
	{
		len++;
		tmp /= 16;
	}
	hex[len] = '\0';
	while (len-- > 0)
	{
		hex[len] = base_char[value % 16];
		value /= 16;
	}
	ft_putstr(hex);
}
