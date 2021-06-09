#include <philosophers.h>

bool	routine_forkmanagement_and_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (print(philo, FORK))
		return (true);
	pthread_mutex_lock(philo->fork_right);
	if (print(philo, FORK))
		return (true);
	if (print(philo, EAT))
		return (true);
	wait_until_death(philo, EAT);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (false);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->name % 2 != 0)
		usleep(1000);
	while (*(philo->someone_died) == false)
	{
		if (routine_forkmanagement_and_eat(philo))
			break ;
		if (philo->in.number_of_steps == philo->nb_eat)
			break ;
		if (print(philo, SLEEP))
			break ;
		wait_until_death(philo, SLEEP);
		if (print(philo, THINK))
			break ;
	}
	pthread_mutex_destroy(&(philo->eat));
	return (NULL);
}
