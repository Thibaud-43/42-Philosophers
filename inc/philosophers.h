
/*
** LIBRARIES
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

/*
** DEFINES
*/

#define SUCCESS			0
#define MALLOC_ERROR	1
#define PTHREAD_ERROR	2
#define TIME			struct timeval
#define MUTEX			pthread_mutex_t

/*
** STRUCTURES
*/

typedef		struct 	t_inputs
{
	useconds_t		time_to_die;
	useconds_t		time_to_sleep;
	useconds_t		time_to_eat;
	useconds_t		max_time_to_think;
	uint32_t		number_of_philosophers;
	uint32_t		number_of_forks;
	uint32_t		number_of_steps;
}					s_inputs;

typedef		struct 	t_philosopher
{
	uint32_t		name;
	pthread_t		thread;
	bool			*someone_died;
	TIME			time_zero;
	TIME			time_last_meal;
	s_inputs		in;
	uint32_t		nb_eat;
	MUTEX			*fork_left;
	MUTEX			*fork_right;
}					s_philosopher;

/*
** GENERAL PROTOTYPES
*/

bool	get_number_of_philosophers_and_forks(char **argv, s_inputs *in);
bool	get_time_to_die(char **argv, s_inputs *in);
bool	get_time_to_eat(char **argv, s_inputs *in);
bool	get_time_to_sleep(char **argv, s_inputs *in);
bool	get_max_time_to_think(char **argv, s_inputs *in);
bool	get_number_of_steps(char **argv, s_inputs *in);
int     create_philosophers(s_inputs *in);
;
/*
** PHILO_ONE
*/

/*
** PHILO_TWO
*/

/*
** PHILO_THREE
*/