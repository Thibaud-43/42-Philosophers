#include <philosophers.h>

bool	get_number_of_steps(char **argv, s_inputs *in)
{
	u_int64_t	nb;
	u_int32_t	i;

	nb = 0;
	i = 0;
	while (argv[5][i])
	{
		nb = nb * 10 + argv[5][i] - 48;
		if (nb > UINT_MAX)
			return (false);
		i++;
	}
	in->number_of_steps = (u_int32_t)nb;
	return (true);
}