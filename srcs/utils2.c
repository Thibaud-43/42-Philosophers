#include <philosophers.h>

void	destroy_mutex(pthread_mutex_t *forks,
t_inputs *in, t_philosopher *philo)
{
	uint32_t	i;

	i = 0;
	while (i < in->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&(philo->eat));
		i++;
	}
	pthread_mutex_destroy((in->use_terminal));
	pthread_mutex_destroy((in->death));
	pthread_mutex_destroy((in->eat));
	free(forks);
}

void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos)
{
	uint32_t	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_mutex_unlock(&forks[i]);
		i++;
	}
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
