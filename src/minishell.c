/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/15 15:41:05 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_failed(char *input, int *exit_status, t_env *minienv)
{
	if (is_empty(input))
		return (TRUE);
	if (has_unclosed_quotes(input))
		return (TRUE);
	if (handle_heredoc(input, exit_status, minienv) == FAILED)
		return (TRUE);
	// TODO: check syntax before splitting
	return (FALSE);
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
		if (input_failed(input, &exit_status, minienv))
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
