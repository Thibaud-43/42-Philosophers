#include <philosophers.h>

bool	get_number_of_philosophers_and_forks(char **argv, s_inputs *in)
{
	u_int64_t	nb;
	u_int32_t	i;

	nb = 0;
	i = 0;
	while (argv[1][i])
	{
		nb = nb * 10 + argv[1][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->number_of_philosophers = (u_int32_t)nb;
	in->number_of_forks = (u_int32_t)nb;
	return (true);
}

bool	get_time_to_die(char **argv, s_inputs *in)
{
	u_int64_t	nb;
	u_int32_t	i;

	nb = 0;
	i = 0;
	while (argv[2][i])
	{
		nb = nb * 10 + argv[2][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->time_to_die = (u_int32_t)nb;
	return (true);
}

bool	get_time_to_eat(char **argv, s_inputs *in)
{
	u_int32_t	nb;
	u_int32_t	i;

	nb = 0;
	i = 0;
	while (argv[3][i])
	{
		nb = nb * 10 + argv[3][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->time_to_eat = (u_int32_t)nb;
	return (true);
}

bool	get_time_to_sleep(char **argv, s_inputs *in)
{
	u_int64_t	nb;
	u_int32_t	i;

	nb = 0;
	i = 0;
	while (argv[4][i])
	{
		nb = nb * 10 + argv[4][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->time_to_sleep = (u_int32_t)nb;
	return (true);
}

bool	get_max_time_to_think(char **argv, s_inputs *in)
{
	in->max_time_to_think = in->time_to_die - in->time_to_sleep - in->time_to_eat;
	return (true);
}