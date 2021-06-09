#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
/*
** LIBRARIES
*/

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>

/*
** DEFINES
*/

# define SUCCESS		0
# define MALLOC_ERROR	1
# define PTHREAD_ERROR	2		
# define WAIT_FREQUENCY	10000

/*
** STRUCTURES AND ENUM
*/

enum		e_mode
{
	EAT,
	SLEEP,
	FORK,
	DIE,
	END,
	THINK,
};

typedef struct s_inputs
{
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	uint64_t		time_to_eat;
	uint64_t		max_time_to_think;
	uint32_t		number_of_philosophers;
	uint32_t		number_of_forks;
	int32_t			number_of_steps;
	pthread_mutex_t	use_terminal;
}					t_inputs;

typedef struct s_philosopher
{
	uint32_t		name;
	pthread_t		thread;
	bool			*someone_died;
	uint64_t		time_zero;
	uint64_t		time_last_meal;
	t_inputs		in;
	int32_t			nb_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	eat;
}					t_philosopher;

/*
** GENERAL PROTOTYPES
*/

bool		get_number_of_philosophers_and_forks(char **argv, t_inputs *in);
bool		get_time_to_die(char **argv, t_inputs *in);
bool		get_time_to_eat(char **argv, t_inputs *in);
bool		get_time_to_sleep(char **argv, t_inputs *in);
bool		get_max_time_to_think(t_inputs *in);
bool		get_number_of_steps(char **argv, t_inputs *in);
int			create_philosophers(t_inputs *in);
void		*routine(void *arg);
uint64_t	get_time(void);
bool		print(t_philosopher *philo, enum e_mode type);
void		wait_until_death(t_philosopher *philo, enum e_mode type);
void		destroy_mutex(pthread_mutex_t *forks, t_inputs *in);
void    	monitoring(t_inputs *in, t_philosopher *philo);



#endif