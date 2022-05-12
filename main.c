/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/12 15:31:08 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input;
	char	**args;
	char	*command;
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
		args = split_args(input);
		command = args[0];
		if (!command)
			continue;
		if (is_builtin(command))
			exit_status = execute_builtin(args, &minienv);
		else
			exit_status = execute_command(args, minienv);
	}
	return (exit_status);
}