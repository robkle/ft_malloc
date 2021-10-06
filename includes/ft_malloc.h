#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdint.h>
# include <sys/mman.h>
# include <pthread.h>
# include "../libft/libft.h"

# define PAGE getpagesize()
# define TINY 256
# define SMALL PAGE
# define N TINY * 256 //65536 (32768 meta 32768 memory)
# define M SMALL * 140 //573440 (49152 meta 524288 memory) 
# define SIZE_PTR sizeof(unsigned long*)
# define FREE 0
# define INUSE 1
# define TAIL 2

typedef struct			s_zone
{
	unsigned long		*tiny;
	unsigned long		*small;
	unsigned long		*large;
}						t_zone;

t_zone					g_zone;

/*
** malloc.c
*/
void			*ft_malloc(size_t size);
void			*ft_add_block(unsigned long **mem, size_t size, \
					size_t map_size);
void			*ft_append_block(unsigned long **mem, unsigned long **block, \
					size_t size, size_t map_size);
void			*ft_insert_block(unsigned long **mem, unsigned long **block, \
				size_t size);

/*
** map.c
*/
void			ft_initiate_page(unsigned long **mem, size_t map_size);
void			ft_append_page(unsigned long **mem, size_t map_size);

/*
** free.c
*/
void			ft_free(void *ptr);
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
void			*ft_realloc(void *ptr, size_t size);

/*
** show.c
*/
void			print_alloc_mem(char *zone, unsigned long *mem, size_t *total);
void			show_alloc_mem();

#endif
