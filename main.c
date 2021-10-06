#include "./includes/ft_malloc.h"
#include <stdio.h>

void	print_mem(unsigned long *mem)
{
	unsigned long	*state;
	
	if (!mem)
		printf("%p\n", mem);
	else
	{
	
		state = mem + 4;
		while (*state != TAIL)
		{
			printf("%lu %lu %#lx |", *state, *(state - 1), *(state + 1));
			state += 3;
		}
		printf("%lu %lu %#lx\n", *state, *(state - 1), *(state + 1));
	}
}

int	main(void)
{
	char	*ptr;
	void	*ptr2;
	void	*ptr3;
	void	*ptr4;

	ptr = ft_malloc(57);
//	ft_memset(ptr, '*', 50);
//	printf("malloc ptr:	");
//	print_mem(g_zone.tiny);
//	printf("%s\n", ptr);
	ptr2 = ft_malloc(323);
//	printf("malloc ptr2:	");
//	print_mem(g_zone.tiny);
//	ptr = ft_realloc(ptr, 116);
	ptr3 = ft_malloc(5000);
	ptr4 = ft_malloc(5698);
	show_alloc_mem();
//	printf("realloc ptr:	");
//	print_mem(g_zone.tiny);
//	printf("%s\n", ptr);
	//ptr3 = ft_malloc(64);
	//printf("malloc ptr3:	");
	//print_mem(g_zone.tiny);
	ft_free (ptr);
//	printf("free ptr:	");
//	print_mem(g_zone.tiny);

	ft_free(ptr2);
	ft_free(ptr3);
	ft_free(ptr4);
//	printf("free ptr2:	");
//	print_mem(g_zone.tiny);
	//ft_free (ptr3);
	//printf("free ptr3:	");
	//print_mem(g_zone.tiny);
	//ft_free (ptr);
	//printf("free ptr:	");
	//print_mem(g_zone.tiny);
	munmap(g_zone.tiny, N); //TEMP
	munmap(g_zone.small, M); //TEMP
	munmap(g_zone.large, 2 * PAGE); //TEMP*/
	
	/*ptr = ft_malloc(100);
	ft_memset(ptr, '*', 99);
	printf("%s\n", ptr);
	printf("map         : %p\n", g_zone.tiny);//TEMP
	printf("map size    : %ld\n", *g_zone.tiny);
	printf("meta size   : %ld\n", *(g_zone.tiny + 1));
	printf("map next    : %#lx\n", *(g_zone.tiny + 2));

	printf("block size  : %ld\n", (unsigned long)*(g_zone.tiny + 3));
	printf("block state : %ld\n", (unsigned long)*(g_zone.tiny + 4));
	printf("block ptr : %#lx\n", (unsigned long)*(g_zone.tiny + 5));
	printf("ptr         : %p\n", ptr);
	printf("ptr - map   : %ld\n", ((unsigned long*)ptr - g_zone.tiny) * 8);
	ft_free(ptr);
	printf("%p\n", g_zone.tiny);
	munmap(g_zone.tiny, N); //TEMP
	
	ptr2 = ft_malloc(5000);
	printf("\nmap         : %p\n", g_zone.large);//TEMP
	printf("map size    : %ld\n", *g_zone.large);
	printf("map next    : %#lx\n", *(g_zone.large + 1));
	printf("block size  : %d\n", (unsigned int)*(g_zone.large + 2));
	printf("block size* : %p\n", g_zone.large + 2);
	printf("block state : %d\n", (unsigned int)*(g_zone.large + 3));
	printf("block state*: %p\n", g_zone.large + 3);
	printf("ptr         : %p\n", ptr2);
	munmap(g_zone.large, 2 * PAGE); //TEMP*/
	
	return (0);
}
