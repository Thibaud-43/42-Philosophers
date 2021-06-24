#include <philosophers.h>

uint64_t	use_time_last_meal(t_philosopher *philo)
{
	uint64_t	ret;

	pthread_mutex_lock(&philo->eat);
	ret = philo->time_last_meal;
	pthread_mutex_unlock(&philo->eat);
	return (ret);
}

bool	eat_max(t_philosopher *philo)
{
	bool	ret;

	pthread_mutex_lock(philo->in.eat);
	if (philo->nb_eat < philo->in.number_of_steps)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(philo->in.eat);
	return (ret);
}

bool	stop(t_philosopher *philo)
{
	bool	ret;

	pthread_mutex_lock(philo->in.death);
	if (*philo->someone_died)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(philo->in.death);
	return (ret);
}

void	wait_until_death(t_philosopher *philo, enum e_mode type)
{
	uint64_t	time;

	if (type == EAT)
		time = philo->in.time_to_eat;
	else if (type == SLEEP)
		time = philo->in.time_to_sleep;
	if (stop(philo) == false)
		ft_sleep(time, philo);
	return ;
}
