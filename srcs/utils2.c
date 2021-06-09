#include <philosophers.h>

void	destroy_mutex(pthread_mutex_t *forks, t_inputs *in)
{
	uint32_t	i;

	i = 0;
	while (i < in->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(in->use_terminal));
	free(forks);
}
