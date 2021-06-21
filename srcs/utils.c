#include <philosophers.h>

char	*ft_itoa(uint64_t num)
{
	char				*dst;
	uint64_t			count;
	uint64_t			i;

	count = ft_count_size(num);
	i = 0;
	if (num < 0 || count == 0)
		count++;
	dst = malloc(sizeof(char) * (count + 1));
	if (!(dst))
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		dst[0] = '-';
		i++;
	}
	dst[count] = '\0';
	while (count > i)
	{
		dst[--count] = (num % 10) + '0';
		num /= 10;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int					s1len;
	int					s2len;
	int					i;
	int					k;
	char				*src;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen((char *) s1);
	s2len = ft_strlen((char *) s2);
	src = malloc((sizeof(char) * (s1len + s2len + 1)));
	if (!(src))
		return (NULL);
	while (k < s1len)
		src[i++] = s1[k++];
	k = 0;
	while (k < s2len)
		src[i++] = s2[k++];
	src[i] = '\0';
	return (src);
}

void	print3(uint64_t time, uint32_t name, char *str)
{
	char	*string;
	char	*tmp;
	char	*tmp2;

	string = ft_itoa(time);
	tmp = string;
	string = ft_strjoin(string, " ms ");
	free(tmp);
	tmp = string;
	tmp2 = ft_itoa(name);
	string = ft_strjoin(string, tmp2);
	free(tmp);
	free(tmp2);
	tmp = string;
	string = ft_strjoin(string, str);
	free(tmp);
	write(1, string, ft_strlen(string));
	free(string);
}

void	print2(t_philosopher *philo, enum e_mode type, uint64_t time_now)
{
	if (type == SLEEP)
		print3((time_now - philo->time_zero),
			philo->name, " is sleeping\n");
	else if (type == THINK)
		print3((time_now - philo->time_zero),
			philo->name, " is thinking\n");
	else if (type == FORK)
		print3((time_now - philo->time_zero),
			philo->name, " has taken a fork\n");
	else if (type == DIE)
		print3((time_now - philo->time_zero),
			philo->name, " is died\n");
	else if (type == END)
		print3((time_now - philo->time_zero),
			philo->name, " has eat enought\n");
}

bool	print(t_philosopher *philo, enum e_mode type)
{
	uint64_t	time_now;

	if (*(philo->someone_died) == true)
		return (true);
	pthread_mutex_lock(&(philo->in.use_terminal));
	time_now = get_time();
	if (type == EAT)
	{
		pthread_mutex_lock(&philo->eat);
		philo->time_last_meal = time_now;
		print3((time_now - philo->time_zero),
			philo->name, " is eating\n");
		pthread_mutex_unlock(&philo->eat);
	}
	else
		print2(philo, type, time_now);
	pthread_mutex_unlock(&(philo->in.use_terminal));
	return (false);
}
