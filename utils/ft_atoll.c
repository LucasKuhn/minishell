#include "minishell.h"

static int	ft_isspace(char c);

long long	ft_atoll(const char *str)
{
	long long	number;
	int			sign;

	number = 0;
	sign = 1;
	while (ft_isspace(*str) && !(*str == '-' || *str == '+'))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}
