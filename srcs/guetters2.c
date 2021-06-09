#include <philosophers.h>

bool	get_number_of_steps(char **argv, t_inputs *in)
{
	uint64_t	nb;
	int32_t		i;

	nb = 0;
	i = 0;
	while (argv[5][i])
	{
		nb = nb * 10 + argv[5][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->number_of_steps = (int32_t)nb;
	return (true);
}
