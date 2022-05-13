/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:16 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/13 18:49:47 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env **minienv, int should_fork)
{
	char *command;
	int		child_pid;
	int		exit_status;

	child_pid = 0;
	exit_status = 0;
	command = args[0];
	if (should_fork)
		child_pid = fork();
	if (child_pid == -1)
		perror("minishell : ");
	else if (child_pid == 0)
	{
		if (str_equal(command, "echo"))
			exit_status = (echo(args));
		if (str_equal(command, "pwd"))
			exit_status = (pwd());
		if (str_equal(command, "env"))
			exit_status = (env(*minienv));
		if (str_equal(command, "export"))
			exit_status = (export(args, minienv));
		if (str_equal(command, "unset"))
			exit_status = (unset(args, minienv));
		if (str_equal(command, "cd"))
			exit_status = (cd(args, *minienv));
		if (str_equal(command, "exit"))
			exit_status = (builtin_exit());
		if (should_fork)
			exit (exit_status);
		return (exit_status);
	}
	else
		wait_for_child(child_pid);
	return(exit_status);
}

int is_builtin(char *command)
{
	if (str_equal(command, "echo"))
		return(1);
	if (str_equal(command, "cd"))
		return(1);
	if (str_equal(command, "pwd"))
		return(1);
	if (str_equal(command, "export"))
		return(1);
	if (str_equal(command, "unset"))
		return(1);
	if (str_equal(command, "env"))
		return(1);
	if (str_equal(command, "exit"))
		return(1);
	return(0);
}
