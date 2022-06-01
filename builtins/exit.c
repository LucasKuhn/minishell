/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:02:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/01 00:27:37 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    fits_in_long_long(char *str)
{
    long long    out;
    int            c;

    if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21)==0)
        return(1);
    out = 0;
    if (*str == '-')
        str++;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        c = *str - '0';
        if (out > (LLONG_MAX - c) / 10)
            return (0);
        out = out * 10 + c;
        str++;
    }
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
	if (!fits_in_long_long(exit_status))
	{
		free_array(args);
		print_error_and_exit("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (args[2] != NULL)
	{
		free_array(args);
		print_error_and_exit("exit", "too many arguments", EXIT_FAILURE);
	}
	number = atoll(exit_status); // TODO: implementar ft_atoll ft_atoull
	exit(number);
}
