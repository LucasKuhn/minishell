/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:16 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/25 19:15:07 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_forked_builtin(char **args, t_env **minienv)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("minishell : ");
		return (EXIT_FAILURE);
	}
	else if (child_pid == 0)
		exit(execute_builtin(args, minienv));
	else
		return (child_pid);
}

int	execute_builtin(char **args, t_env **minienv)
{
	char	*command;

	command = args[0];
	if (str_equal(command, "echo"))
		return (echo(args));
	if (str_equal(command, "pwd"))
		return (pwd());
	if (str_equal(command, "env"))
		return (env(*minienv));
	if (str_equal(command, "export"))
		return (export(args, minienv));
	if (str_equal(command, "unset"))
		return (unset(args, minienv));
	if (str_equal(command, "cd"))
		return (cd(args, *minienv));
	if (str_equal(command, "exit"))
		return (builtin_exit());
	else
		return (EXIT_FAILURE);
}

int	is_builtin(char *command)
{
	if (!command)
		return(0);
	if (str_equal(command, "echo"))
		return (1);
	if (str_equal(command, "cd"))
		return (1);
	if (str_equal(command, "pwd"))
		return (1);
	if (str_equal(command, "export"))
		return (1);
	if (str_equal(command, "unset"))
		return (1);
	if (str_equal(command, "env"))
		return (1);
	if (str_equal(command, "exit"))
		return (1);
	return (0);
}
