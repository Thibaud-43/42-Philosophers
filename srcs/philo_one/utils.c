#include <philosophers.h>

uint64_t get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

bool    print(s_philosopher   *philo, enum mode type)
{
    uint64_t         time_now;

    if (*(philo->someone_died) == true)
            return (true);
    pthread_mutex_lock(&(philo->in.use_terminal));
    time_now = get_time();
    if (type == EAT)
    {
        philo->time_last_meal = time_now;
        printf("%ld %d %s\n", (time_now - philo->time_zero), philo->name, "is eating");
    }
    else if (type == SLEEP)
        printf("%ld %d %s\n", (time_now - philo->time_zero), philo->name, "is sleeping");
    else if (type == THINK)
        printf("%ld %d %s\n", (time_now - philo->time_zero), philo->name, "is thinking");
    else if (type == FORK)
        printf("%ld %d %s\n", (time_now - philo->time_zero), philo->name, "has taken a fork");
    else if (type == DIE)
        printf("%ld %d %s\n", (time_now - philo->time_zero), philo->name, "is died");
    pthread_mutex_unlock(&(philo->in.use_terminal));
    return (false);
}

void    wait_until_death(s_philosopher   *philo, enum mode type)
{
    uint64_t    time;
    uint64_t    steps;

    if (type == EAT)
        time = philo->in.time_to_eat * 1000;
    else if (type == SLEEP)
        time = philo->in.time_to_sleep * 1000;
    steps = (time / WAIT_FREQUENCY);
    while (steps && *(philo->someone_died) == false)
    {
        if (get_time() - philo->time_last_meal >= philo->in.time_to_die)
        {
            print(philo, DIE);
            *(philo->someone_died) = true;
            return ;
        }
        usleep(WAIT_FREQUENCY);
        steps--;
    }
    usleep(time % WAIT_FREQUENCY);
    if (get_time() - philo->time_last_meal >= philo->in.time_to_die)
    {
        print(philo, DIE);
        *(philo->someone_died) = true;
        return ;
    }
}