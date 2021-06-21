#include <philosophers.h>

void	wait_until_death(t_philosopher *philo, enum e_mode type)
{
	uint64_t	time;

	if (type == EAT)
		time = philo->in.time_to_eat;
	else if (type == SLEEP)
		time = philo->in.time_to_sleep;
	if ((*philo->someone_died) == false)
		ft_sleep(time, philo);
	return ;
}
