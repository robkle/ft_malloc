#include "ft_malloc.h"
#include <stdio.h>

void	*ft_insert_block(unsigned long **mem, unsigned long **block, \
			size_t size)
{
	void	*ptr;
	size_t	alloc_size;

	//if (**block == size)//OLD
	if (**block == alloc_size)//REAL SIZE
	{
		**block = size; //REAL SIZE
		*(*block + 1) = INUSE;
		ptr = (void*)*(*block + 2);
	}
	//else if (**block > size)//OLD
	else if (**block > alloc_size)//REAL_SIZE
	{
		ft_memmove((void*)(*block + 3), (void*)*block, \
			(size_t)(*(*mem + 1) - ((*block + 3) - *mem)));
		**block = size;
		*(*block + 1) = INUSE;
		*(*block + 2) = *(*block + 5);
		*(*block + 3) -= alloc_size;//REAL SIZE
		//*(*block + 3) -= size; //OLD
		*(*block + 4) = FREE;
		*(*block + 5) += alloc_size; //REAL_SIZE
		//*(*block + 5) += size;//OLD
		ptr = (void*)*(*block + 2);
	}
	return (ptr);		
}

void	*ft_append_block(unsigned long **mem, unsigned long **block, \
			size_t size, size_t map_size)
{
	size_t	alloc_size;//REAL SIZE

	alloc_size = (size + 31) & -32;//REAL SIZE
	//if (**block < size)//OLD
	if (**block < alloc_size) //REAL SIZE
	{
		ft_append_page(mem, map_size);
		*block = (unsigned long*)*(*mem + 2) + 3;
	}
	*(*block + 3) = **block - alloc_size; //REAL SIZE
	//*(*block + 3) = **block - size; //OLD
	*(*block + 4) = TAIL; 
	*(*block + 5) = *(*block + 2) + alloc_size; //REAL_SIZE
	//*(*block + 5) = *(*block + 2) + size; //OLD
	**block = size;
	*(*block + 1) = INUSE;
	return ((void*)*(*block + 2));
}

void	*ft_add_block(unsigned long **mem, size_t size, size_t map_size)
{
	unsigned long	*block_size;
	unsigned long	*block_state;

	block_size = *mem + 3;
	block_state = *mem + 4;
	while (1)
	{
		//if (*block_state == FREE && size <= *block_size)OLD
		if (*block_state == FREE && ((size + 31) & -32) <= *block_size)//REAL SIZE
			return (ft_insert_block(mem, &block_size, size));
		else if (*block_state == TAIL)
			return (ft_append_block(mem, &block_size, size, map_size));
		block_size = block_size + 3; 
		block_state = block_state + 3; 
	}
	return (NULL);
}

void	*ft_malloc(size_t size)
{
	size_t			alloc_size;
	unsigned long	**mem;
	int				map_size;
	
	if (size <= 0)//create check size function to check upper size limit - getrlimit
		return (NULL);
	alloc_size = (size + 31) & -32;
	/*
	** Put next 15 lines of code in separate function(s):
	** map_size = ft_allocate_zone(&mem, alloc_size);
	*/
	if (alloc_size <= TINY)
	{
		mem = &g_zone.tiny;
		map_size = N;
	}
	else if (alloc_size <= SMALL)
	{
		mem = &g_zone.small;
		map_size = M;
	}
	else
	{
		mem = &g_zone.large;
		map_size = (alloc_size + 128 + (PAGE - 1)) & -PAGE;
	}
	if (!(*mem))
		ft_initiate_page(mem, map_size);
	//return (ft_add_block(mem, alloc_size, map_size));OLD
	return (ft_add_block(mem, size, map_size)); //REAL SIZE
}
