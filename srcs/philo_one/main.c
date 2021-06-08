#include <philosophers.h>

void	init_inputs(s_inputs *in)
{
	in->time_to_die = 0;
	in->time_to_sleep = 0;
	in->time_to_eat = 0;
	in->max_time_to_think = 0;
	in->number_of_philosophers = 0;
	in->number_of_forks = 0;
	in->number_of_steps = -1;
	pthread_mutex_init(&in->use_terminal, NULL);
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

bool	get_inputs(int argc, char **argv, s_inputs *in)
{
	bool ret;

	ret = true;
	ret = get_number_of_philosophers_and_forks(argv, in);
	ret = get_time_to_die(argv, in);
	ret = get_time_to_eat(argv, in);
	ret = get_time_to_sleep(argv, in);
	ret = get_max_time_to_think(argv, in);
	if (argc == 6)	
		ret = get_number_of_steps(argv, in);
	return (ret);
}
void	print_inputs(s_inputs *in)
{
	printf("time_to_die: %lu \n", in->time_to_die);
	printf("time_to_sleep: %lu \n", in->time_to_sleep);
	printf("time_to_eat: %lu \n", in->time_to_eat);
	printf("max_time_to_think: %lu \n", in->max_time_to_think);
	printf("number_of_philosophers: %u \n", in->number_of_philosophers);
	printf("number_of_forks: %u \n", in->number_of_forks);
	printf("number_of_steps: %u \n", in->number_of_steps );
}

int 	main(int argc, char **argv)
{
	s_inputs	in;

	init_inputs(&in);
	if (parse_inputs(argc, argv) == false || get_inputs(argc, argv, &in) == false)
	{
		printf("Error in arguments.\n");
		return (SUCCESS);
	}
	//print_inputs(&in);
	create_philosophers(&in);
	return (SUCCESS);
}