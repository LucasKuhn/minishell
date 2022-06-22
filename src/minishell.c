/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/21 15:49:05 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (is_empty(input) || has_input_error(input, &exit_status, minienv))
			continue ;
		handle_expansions(&input, minienv, exit_status);
		if (!has_pipe(input))
			exit_status = execute_one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			exit_status = execute_multiple_commands(commands, &minienv);
			free_array(commands);
		}
		free(input);
	}
	return (exit_status);
}
