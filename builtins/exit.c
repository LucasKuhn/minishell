/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:02:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/31 17:02:57 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_long(const char *str)
{
	long long	number;
	int		i;

	if (ft_strlen(str) > 20)
		return (0);
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-' && str[i + 1])
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	number = atoll(str); // TODO: implementar ft_atoll
	if (number > MAX_LONG || number < MIN_LONG)
		return (0);
	return (1);
}

int	builtin_exit(char **args, t_env **minienv)
{
	char	*exit_status;
	long	number;

	rl_clear_history();
	free_minienv(minienv);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[0] || !args[1])
	{
		free_array(args);
		exit(EXIT_SUCCESS);
	}
	exit_status = args[1];
	if (!str_is_long(exit_status))
	{
		free_array(args);
		print_error_and_exit("exit", "numeric argument required", OUT_OF_RANGE);
	}
	if (args[2] != NULL)
	{
		free_array(args);
		print_error_and_exit("exit", "too many arguments", EXIT_FAILURE);
	}
	number = ft_atol(exit_status);
	exit(number);
}
