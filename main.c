/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/10 19:04:02 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	char **args;
	char *command;
	t_env *minienv;

	signals();
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
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO); // TODO: caso especial depois de Ctrl+C imprime uma linha em branco
			// rl_on_new_line();
			// rl_replace_line("", 0);
			exit(0);
		}
		else
			execute_command(args, minienv);
	}
}
