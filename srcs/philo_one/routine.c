#include <philosophers.h>

void* routine(void* arg) 
{
    s_philosopher   *philo;
    uint64_t         time_now;
 
    philo = (s_philosopher *)arg;
    if (philo->name % 2 != 0)
        usleep(1000);
    while (*(philo->someone_died) == false && philo->nb_eat != philo->in.number_of_steps)
    {
        pthread_mutex_lock(philo->fork_left);
        if (print(philo, FORK))
            break;
        pthread_mutex_lock(philo->fork_right);
        if (print(philo, FORK))
            break ;
        if (print(philo, EAT))
            break ;
        wait_until_death(philo, EAT);
        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(philo->fork_right);
        if (print(philo, SLEEP))
            break ;
        wait_until_death(philo, SLEEP);
        if (print(philo, THINK))
            break ;
        if (philo->in.number_of_steps != -1)
            philo->nb_eat++;
    }
}