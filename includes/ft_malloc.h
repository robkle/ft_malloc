/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:50 by rklein            #+#    #+#             */
/*   Updated: 2021/11/05 15:03:06 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdint.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>

/*
** N = 24576 bytes meta space + 28672 bytes allocation space = 53248 bytes
** 28672 = (256 * 100) rounded up to multiple of 4096
** M = 36864 bytes meta space + 409600 bytes allocation space = 446464 bytes
** 409600 = 4096 * 100
** meta consists of 24 bytes of meta data for each block + 24 bytes of meta
** data for the mapped memory space. Memory allocations are rounded up to
** the next multiple of 32 bytes, therefore the smallest block is 32 bytes.
** Thus:
** ((28672 / 32) * 24) rounded up to multiple of 4096 = 24576 bytes meta space
** ((409600 / 288) * 24) rounded up to multiple of 4096 = 36864 bytes meta space
*/
# define PAGE 4096
# define TINY 256
# define SMALL PAGE
# define N 53248
# define M 446464 
# define FREE 0
# define INUSE 1
# define TAIL 2

typedef struct s_zone
{
	unsigned long		*tiny;
	unsigned long		*small;
	unsigned long		*large;
}					t_zone;

t_zone				g_zone;
pthread_mutex_t		g_mutex;

/*
** malloc.c
*/
void			*malloc(size_t size);
void			*ft_alloc(size_t size);
void			*ft_add_block(unsigned long **mem, size_t size, \
					size_t map_size);
void			*ft_append_block(unsigned long **block, size_t size);
void			*ft_insert_block(unsigned long **mem, unsigned long **block, \
				size_t size);

/*
** limit.c
*/
int				ft_size_limit(size_t size);

/*
** map.c
*/
void			ft_initiate_page(unsigned long **mem, size_t map_size);
void			*ft_append_page(unsigned long **mem, size_t map_size, \
				size_t size);

/*
** free.c
*/
void			free(void *ptr);
void			ft_free_block(unsigned long *ptr);

/*
** locate.c
*/
unsigned long	*ft_valid_ptr(unsigned long **map, void *ptr);
unsigned long	*ft_scan_map(unsigned long **zone, void *ptr);
unsigned long	*ft_find_map(void *ptr);
void			ft_get_zone(size_t size, size_t *map_size, \
					unsigned long ***mem);

/*
** defragment.c
*/
void			ft_defragment(unsigned long **map);

/*
** unmap.c
*/
void			ft_unmap(unsigned long **map);
void			ft_free_map(unsigned long map_size);

/*
** realloc.c
*/
void			ft_copy_from_swap(void *ptr, unsigned long **swap);
void			ft_copy_to_swap(unsigned long *meta, unsigned long **swap);
void			*ft_find_free_alloc(void *ptr, size_t size);
void			*realloc(void *ptr, size_t size);

/*
** show.c
*/
void			print_alloc_mem(char *zone, unsigned long *mem, size_t *total);
void			show_alloc_mem(void);

/*
** UTILS
*/
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_puthex(unsigned long value);
void			ft_putsize(size_t n);
void			ft_putstr(char const *s);

#endif
