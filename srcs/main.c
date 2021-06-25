#include <philosophers.h>

void	init_inputs(t_inputs *in)
{
	pthread_mutex_t	*term;
	pthread_mutex_t	*death;
	pthread_mutex_t	*eat;

	term = malloc(sizeof(pthread_mutex_t));
	death = malloc(sizeof(pthread_mutex_t));
	eat = malloc(sizeof(pthread_mutex_t));
	in->time_to_die = 0;
	in->time_to_sleep = 0;
	in->time_to_eat = 0;
	in->max_time_to_think = 0;
	in->number_of_philosophers = 0;
	in->number_of_forks = 0;
	in->number_of_steps = -1;
	pthread_mutex_init((term), NULL);
	pthread_mutex_init((death), NULL);
	pthread_mutex_init((eat), NULL);
	in->use_terminal = term;
	in->death = death;
	in->eat = eat;
}

bool	only_numbers(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

bool	parse_inputs(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc > 6 || argc < 5)
		return (false);
	while (i < argc)
	{
		if (only_numbers(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	get_inputs(int argc, char **argv, t_inputs *in)
{
	bool	ret;

	ret = true;
	ret = get_number_of_philosophers_and_forks(argv, in);
	ret = get_time_to_die(argv, in);
	ret = get_time_to_eat(argv, in);
	ret = get_time_to_sleep(argv, in);
	ret = get_max_time_to_think(in);
	if (argc == 6)
		ret = get_number_of_steps(argv, in);
	if (in->number_of_philosophers > 200
		|| in->time_to_die < 60
		|| in->time_to_eat < 60 || in->time_to_sleep < 60
		|| (in->number_of_steps != -1 && in->number_of_steps < 0))
		ret = false;
	return (ret);
}

int 	main(int argc, char **argv)
{
	t_inputs	in;

	init_inputs(&in);
	if (parse_inputs(argc, argv) == false
		|| get_inputs(argc, argv, &in) == false)
	{
		printf("Error in arguments.\n");
		free(in.use_terminal);
		free(in.eat);
		free(in.death);
		return (SUCCESS);
	}
	if (in.number_of_philosophers < 2)
	{
		print3((in.time_to_die),
			0, " is died\n");
		free(in.use_terminal);
		free(in.eat);
		free(in.death);
	}
	else
		create_philosophers(&in);
	return (SUCCESS);
}
