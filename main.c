/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/11 17:27:49 by lalex-ku         ###   ########.fr       */
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

	exit_status = 0;
	minienv = init_minienv(envp);
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!input)
			builtin_exit();
		args = split_args(input);
		command = args[0];
		if (!command)
			continue;
		if (str_equal(command, "echo"))
			echo(args);
		else if (str_equal(command, "pwd"))
			pwd(args);
		else if (str_equal(command, "env"))
			env(args, minienv);
		else if (str_equal(command, "export"))
			export(args, &minienv);
		else if (str_equal(command, "unset"))
			unset(args, &minienv);
		else if (str_equal(command, "cd"))
			cd(args, minienv);
		else if (str_equal(command, "exit"))
			builtin_exit();
		else
			exit_status = execute_command(args, minienv);
	}
}