#include <philosophers.h>

uint64_t get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void* routine(void* arg) 
{
    s_philosopher   *philo;
    uint64_t         time_now;
 

    philo = (s_philosopher *)arg;
    while (*(philo->someone_died) == false && philo->nb_eat != philo->in.number_of_steps)
    {
        if (philo->name % 2 != 0)
            usleep(1000);
        pthread_mutex_lock(philo->fork_left);
        time_now = get_time();
        printf("%ld %d has taken a fork\n", (time_now - philo->time_zero), philo->name);
        pthread_mutex_lock(philo->fork_right);
        time_now = get_time();
        printf("%ld %d has taken a fork\n", (time_now - philo->time_zero), philo->name);

        philo->time_last_meal = get_time();
        printf("%ld %d is eating\n", (philo->time_last_meal - philo->time_zero), philo->name);
        usleep(philo->in.time_to_eat * 1000);
        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(philo->fork_right);
        
        time_now = get_time();
        printf("%ld %d is sleeping\n", (time_now - philo->time_zero), philo->name);
        usleep(philo->in.time_to_sleep * 1000);
        
        
        time_now = get_time();
        printf("%ld %d is thinking\n", (time_now- philo->time_zero), philo->name);
        if (philo->in.number_of_steps != -1)
            philo->nb_eat++;
    }
}

int     init_forks(s_inputs *in, MUTEX **forks, s_philosopher **philo)
{
    int         i;
    int         k;

    i = 0;
    (*forks) = malloc(sizeof(MUTEX) * (in->number_of_philosophers));
    if (!(*forks))
        return (MALLOC_ERROR);
    while (i < in->number_of_philosophers)
    {
        if (i == 0)
        {
            (*philo)[i].fork_left = &((*forks)[i]);
            (*philo)[i].fork_right = &((*forks)[in->number_of_philosophers - 1]);
        }
        else
        {
            (*philo)[i].fork_left = &((*forks)[i]);
            (*philo)[i].fork_right = &((*forks)[i - 1]);
        }
        i++;
    }
    while (k <= i)
    {
        pthread_mutex_init(&((*forks)[k]), NULL);
        k++;
    }
    return (SUCCESS);
}

int     init_philosophers(uint64_t time_zero, bool *someone_died, s_philosopher **philo, s_inputs *in)
{
    int         i;

    i = 0;
    (*philo) = malloc(sizeof(s_philosopher) * (in->number_of_philosophers));
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

int     create_philosophers(s_inputs *in)
{
    s_philosopher   *philo;
    MUTEX           *forks;
    uint64_t            time_zero;
    bool            someone_died;
    int             i;
    

    time_zero = get_time();
    someone_died = false;
    if (init_philosophers(time_zero, &someone_died, &philo, in) == MALLOC_ERROR || 
    init_forks(in, &forks, &philo) == MALLOC_ERROR)
        return (MALLOC_ERROR);
    i = 0;
	while (i < in->number_of_philosophers)
    {
        if (pthread_create(&(philo[i].thread), NULL, &routine, &(philo[i])) != 0)
            return (PTHREAD_ERROR);
        i++;
    }
    i = 0;
	while (i < in->number_of_philosophers)
    {
        if (pthread_join(philo[i].thread, NULL) != 0)
            return (PTHREAD_ERROR);
        i++;
    }
    free(philo);
    return (SUCCESS);
}