#include "../includes/ft_malloc.h"

void	threadFunc1(void *arg)
{
	void	**addr;

	addr = (void**)arg;
	*addr = malloc(64);
}

void	threadFunc2(void *arg)
{
	void	**addr;

	addr = (void**)arg;
	*addr = malloc(128);
}

void	threadFunc3(void *arg)
{
	void	**addr;

	addr = (void**)arg;
	*addr = malloc(256);
}

int	main()
{
	char 		*addr[3];
	pthread_t	thread[3];

	pthread_create(&thread[0], NULL, (void*)&threadFunc1, (void*)&addr[0]);
	pthread_create(&thread[1], NULL, (void*)&threadFunc2, (void*)&addr[1]);
	pthread_create(&thread[2], NULL, (void*)&threadFunc3, (void*)&addr[2]);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	show_alloc_mem();
	return (0);
}
