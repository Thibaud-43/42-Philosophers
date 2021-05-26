
/*
** LIBRARIES
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

/*
** STRUCTURES
*/

typedef		struct 	t_inputs
{
	useconds_t		time_to_die;
	useconds_t		time_to_sleep;
	useconds_t		time_to_eat;
	useconds_t		max_time_to_think;
	u_int32_t		number_of_philosophers;
	u_int32_t		number_of_forks;
	int32_t			number_of_steps;

}					s_inputs;

/*
** GENERAL PROTOTYPES
*/

bool	get_number_of_philosophers_and_forks(char **argv, s_inputs *in);
bool	get_time_to_die(char **argv, s_inputs *in);
bool	get_time_to_eat(char **argv, s_inputs *in);
bool	get_time_to_sleep(char **argv, s_inputs *in);
bool	get_max_time_to_think(char **argv, s_inputs *in);
bool	get_number_of_steps(char **argv, s_inputs *in);
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