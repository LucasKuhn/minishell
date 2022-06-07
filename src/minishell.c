/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/07 16:32:22 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains_pipe(char *str)
{
	while (*str)
	{
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!*input || has_unclosed_quotes(input) || is_empty(input))
			continue ;
		// TODO: check syntax before splitting
		handle_expansions(&input, minienv, exit_status);
		if (!contains_pipe(input))
			exit_status = execute_one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			exit_status = execute_multiple_commands(commands, &minienv);
			free_array(commands);
		}
	}
	return (exit_status);
}
