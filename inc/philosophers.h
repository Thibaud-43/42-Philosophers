
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
#define DEBUG			write(1, "ok\n", 3);
#define WAIT_FREQUENCY	10000

/*
** STRUCTURES AND ENUM
*/

enum		mode
{
	EAT,
	SLEEP,
	FORK,
	DIE,
	END,
	THINK,
};

typedef		struct 	t_inputs
{
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	uint64_t		time_to_eat;
	uint64_t		max_time_to_think;
	uint32_t		number_of_philosophers;
	uint32_t		number_of_forks;
	int32_t			number_of_steps;
	MUTEX			use_terminal;
}					s_inputs;

typedef		struct 	t_philosopher
{
	uint32_t		name;
	pthread_t		thread;
	bool			*someone_died;
	uint64_t		time_zero;
	uint64_t		time_last_meal;
	s_inputs		in;
	uint32_t		nb_eat;
	MUTEX			*fork_left;
	MUTEX			*fork_right;
}					s_philosopher;

/*
** GENERAL PROTOTYPES
*/

bool		get_number_of_philosophers_and_forks(char **argv, s_inputs *in);
bool		get_time_to_die(char **argv, s_inputs *in);
bool		get_time_to_eat(char **argv, s_inputs *in);
bool		get_time_to_sleep(char **argv, s_inputs *in);
bool		get_max_time_to_think(char **argv, s_inputs *in);
bool		get_number_of_steps(char **argv, s_inputs *in);
int     	create_philosophers(s_inputs *in);
void*		routine(void* arg);
uint64_t 	get_time(void);
bool    	print(s_philosopher   *philo, enum mode type);
void    	wait_until_death(s_philosopher   *philo, enum mode type);



/*
** PHILO_ONE
*/

/*
** PHILO_TWO
*/

/*
** PHILO_THREE
*/