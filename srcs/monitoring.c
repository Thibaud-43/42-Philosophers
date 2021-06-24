#include <philosophers.h>

void	ft_sleep(uint64_t ms, t_philosopher *philo)
{
	uint64_t	curr;
	uint64_t	end;

	curr = get_time();
	end = curr + ms;
	while (get_time() < end && stop(philo) == false)
		usleep(100);
}

bool	is_dead(t_philosopher *philo)
{
	if (stop(philo) == true)
		return (true);
	if (get_time() - use_time_last_meal(philo) >= philo->in.time_to_die)
	{
		pthread_mutex_lock(&philo->eat);
		pthread_mutex_lock(philo->in.death);
		(*philo->someone_died) = true;
		pthread_mutex_unlock(philo->in.death);
		pthread_mutex_lock(philo->in.use_terminal);
		print3((get_time() - philo->time_zero),
			philo->name, " died\n");
		pthread_mutex_unlock(philo->in.use_terminal);
		pthread_mutex_unlock(&philo->eat);
		return (true);
	}
	return (false);
}

bool	check_eat(t_philosopher *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo[0].in.number_of_philosophers
		&& stop(philo) == false)
	{
		if (eat_max(philo + i))
			return (false);
		i++;
	}
	return (true);
}

bool	check_death(t_philosopher *philo)
{
	uint32_t	i;

	i = 0;
	while (i < philo[0].in.number_of_philosophers
		&& stop(philo) == false)
	{
		if (is_dead(&philo[i]))
			return (true);
		i++;
	}
	return (false);
}

void	monitoring(t_inputs *in, t_philosopher *philo)
{
	while (stop(philo) == false)
	{
		ft_sleep(8, philo);
		if (check_death(philo))
			break ;
		if (stop(philo) == false && in->number_of_steps > 0
			&& check_eat(philo))
		{
			pthread_mutex_lock(philo->in.death);
			(*philo->someone_died) = true;
			pthread_mutex_unlock(philo->in.death);
			ft_sleep(5, philo);
			printf("Everyone ate well\n");
			break ;
		}
	}
}
