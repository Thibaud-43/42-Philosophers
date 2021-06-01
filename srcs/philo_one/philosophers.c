#include <philosophers.h>

void* routine(void* arg) 
{
    s_philosopher   philo;
    TIME            time_now;

    philo = *(s_philosopher *)arg;
    gettimeofday(&time_now, NULL);
    printf("Time %ld : Philo %d has started\n", (time_now.tv_usec - philo.time_zero.tv_usec), philo.name);
}

int     init_forks(s_inputs *in, MUTEX **forks, s_philosopher **philo)
{
    int         i;

    i = 0;
    (*forks) = malloc(sizeof(MUTEX) * (in->number_of_philosophers));
    if (!(*forks))
        return (MALLOC_ERROR);
    while (i < in->number_of_philosophers)
    {
        if (i == 0)
        {
            (*philo)[i].fork_left = forks[i];
            (*philo)[i].fork_right = forks[in->number_of_philosophers - 1];
        }
        else
        {
            (*philo)[i].fork_left = forks[i];
            (*philo)[i].fork_right = forks[i - 1];
        }
        i++;
    }
    return (SUCCESS);
}

int     init_philosophers(TIME time_zero, bool *someone_died, s_philosopher **philo, s_inputs *in)
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
    TIME            time_zero;
    bool            someone_died;
    int             i;
    

    gettimeofday(&time_zero, NULL);
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
        printf("Thread %d has stopped\n", i);
        i++;
    }
    free(philo);
    return (SUCCESS);
}