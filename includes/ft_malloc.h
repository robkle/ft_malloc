/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:55:50 by rklein            #+#    #+#             */
/*   Updated: 2021/10/29 14:26:45 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdint.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>

//# define PAGE getpagesize()
# define PAGE 4096
# define TINY 256
# define SMALL PAGE
//# define N TINY * 256 //65536 (32768 meta 32768 memory)
//# define M SMALL * 140 //573440 (49152 meta 524288 memory)
//# define N 65536
//# define M 573440 
//NEW TINY 53248 (24576 meta 28672 memory)
//NEW SMALL 446464 (36864 meta 4096600 memory) 
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
}			t_zone;

t_zone			g_zone;
pthread_mutex_t		g_mutex;

/*
** malloc.c
*/
void			*malloc(size_t size);
void			ft_get_zone(size_t size, size_t *map_size, \
					unsigned long ***mem);
void			*ft_add_block(unsigned long **mem, size_t size, \
					size_t map_size);
void			*ft_append_block(unsigned long **block, size_t size);
void			*ft_insert_block(unsigned long **mem, unsigned long **block, \
				size_t size);

/*
** limit.c
*/
int			ft_size_limit(size_t size);

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
