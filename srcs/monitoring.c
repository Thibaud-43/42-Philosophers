#include <philosophers.h>

void	ft_sleep(uint32_t ms)
{
	uint32_t	curr;
	uint32_t	end;

	curr = get_time();
	end = curr + ms;
	while (get_time() < end)
		usleep(100);
}

bool	is_dead(t_philosopher *philo)
{
	if (*philo->someone_died == true)
		return (true);
	pthread_mutex_lock(&philo->eat);
	if (get_time() - philo->time_last_meal >= philo->in.time_to_die)
	{
		if (*philo->someone_died == false)
		{
			*philo->someone_died = true;
			pthread_mutex_lock(&philo->in.use_terminal);
			printf("%lums %u died\n", (get_time() - philo->time_zero),
				philo->name);
			pthread_mutex_unlock(&philo->in.use_terminal);
		}
		pthread_mutex_unlock(&philo->eat);
		return (true);
	}
	pthread_mutex_unlock(&philo->eat);
	return (false);
}

bool	check_meals(t_philosopher *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo[0].in.number_of_philosophers)
	{
		if (philo[i].nb_eat < philo[i].in.number_of_steps)
			return (false);
		i++;
	}
	return (true);
}

bool	check_death(t_philosopher *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo[0].in.number_of_philosophers)
	{
		if (is_dead(&philo[i]))
			return (true);
		i++;
	}
	return (false);
}

void	monitoring(t_inputs *in, t_philosopher *philo)
{
	while (*philo->someone_died == false)
	{
		ft_sleep(8);
		check_death(philo);
		if (*philo->someone_died == false && in->number_of_steps > 0
			&& check_meals(philo))
		{
			*philo->someone_died = true;
			ft_sleep(5);
			printf("Everyone ate well\n");
		}
	}
}
