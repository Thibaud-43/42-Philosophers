#include <philosophers.h>

void	init_forks2(t_inputs *in, pthread_mutex_t **forks,
		t_philosopher **philo, uint32_t *i)
{
	while (*i < in->number_of_philosophers)
	{
		if (*i == 0)
		{
			(*philo)[*i].fork_left = &((*forks)[*i]);
			(*philo)[*i].fork_right = &((*forks)
				[in->number_of_philosophers - 1]);
		}
		else
		{
			(*philo)[*i].fork_left = &((*forks)[*i]);
			(*philo)[*i].fork_right = &((*forks)[*i - 1]);
		}
		(*i)++;
	}
}

int	init_forks(t_inputs *in, pthread_mutex_t **forks, t_philosopher **philo)
{
	uint32_t	i;
	uint32_t	k;

	i = 0;
	k = 0;
	(*forks) = malloc(sizeof(pthread_mutex_t) * (in->number_of_philosophers));
	if (!(*forks))
		return (MALLOC_ERROR);
	init_forks2(in, forks, philo, &i);
	while (k < i)
	{
		pthread_mutex_init(&((*forks)[k]), NULL);
		k++;
	}
	return (SUCCESS);
}

int	init_philosophers(uint64_t time_zero, bool *someone_died,
	t_philosopher **philo, t_inputs *in)
{
	uint32_t	i;

	i = 0;
	(*philo) = malloc(sizeof(t_philosopher) * (in->number_of_philosophers));
	if (!(*philo))
		return (MALLOC_ERROR);
	while (i < in->number_of_philosophers)
	{
		(*philo)[i].name = i;
		(*philo)[i].someone_died = someone_died;
		(*philo)[i].in = (*in);
		(*philo)[i].time_zero = time_zero;
		(*philo)[i].time_last_meal = time_zero;
		(*philo)[i].nb_eat = 0;
		i++;
	}
	return (SUCCESS);
}

int	create_philosophers2(t_inputs *in, t_philosopher *philo)
{
	uint32_t		i;

	i = 0;
	while (i < in->number_of_philosophers)
	{
		if (pthread_create(&(philo[i].thread), NULL,
				&routine, &(philo[i])) != 0)
			return (PTHREAD_ERROR);
		i++;
	}
	monitoring(in, philo);
	i = 0;
	while (i < in->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (PTHREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	create_philosophers(t_inputs *in)
{
	t_philosopher	*philo;
	pthread_mutex_t	*forks;
	uint64_t		time_zero;
	bool			someone_died;

	time_zero = get_time();
	someone_died = false;
	if (init_philosophers(time_zero, &someone_died, &philo, in)
		== MALLOC_ERROR || init_forks(in, &forks, &philo)
		== MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (create_philosophers2(in, philo) == PTHREAD_ERROR)
		return (PTHREAD_ERROR);
	free(philo);
	destroy_mutex(forks, in);
	return (SUCCESS);
}
