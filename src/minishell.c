/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/26 11:53:39 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;
	char	*command;

	exit_status = 0;
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!*input || has_unclosed_quotes(input) || is_empty(input))
			continue ;
		// TODO: check syntax before splitting
		commands = split_commands(input);
		expand_variables(commands, minienv, exit_status);
		if (commands[1] == NULL)
		{
			command = ft_strdup(commands[0]);
			free_array(commands);
			exit_status = execute_one_command(command, &minienv);
		}
		else
		{
			exit_status = execute_multiple_commands(commands, &minienv);
			free_array(commands);			
		}
	}
	return (exit_status);
}
