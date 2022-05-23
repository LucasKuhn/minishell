/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/23 17:29:19 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int minishell(t_env	*minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = 0;
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!*input || has_unclosed_quotes(input))
			continue;
		// TODO: check syntax before splitting
		commands = split_commands(input); //TODO: limpar commands
		if (commands[1] == NULL)
			exit_status = execute_one_command(commands[0], &minienv);
		else
			exit_status = execute_multiple_commands(commands, &minienv);
	}
	return (exit_status);
}