/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/09 15:08:42 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	char **args;
	char *command;
	t_env *minienv;

	minienv = init_minienv(envp);
	while (1)
	{
		input = prompt_input(minienv);
		args = ft_split(input, ' ');
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
			exit(0);
	}
}
