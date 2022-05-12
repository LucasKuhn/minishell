/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/12 16:59:11 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input;
	char	**args;
	char	**commands;
	char	*command_name;
	t_env	*minienv;

	(void) argc;
	(void) argv;
	exit_status = 0;
	minienv = init_minienv(envp);
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!input)
			builtin_exit(args, &minienv);
		commands = split_commands(input);
		while (*commands)
		{
			args = split_args(*commands);
			command_name = args[0];
			if (!command_name)
				continue;
			if (is_builtin(command_name))
				exit_status = execute_builtin(args, &minienv);
			else
				exit_status = execute_command(args, minienv);
			commands++;
		}
	}
	return (exit_status);
}
