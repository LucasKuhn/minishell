/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:26:29 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/28 18:51:00 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_forked_builtin(char **args, t_env **minienv)
{
	int	exit_status;

	exit_status = execute_builtin(args, minienv);
	free_array(args);
	free_minienv(minienv);
	rl_clear_history();
	exit(exit_status);
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
		return (builtin_export(args, minienv));
	if (str_equal(command, "unset"))
		return (unset(args, minienv));
	if (str_equal(command, "cd"))
		return (cd(args, *minienv));
	if (str_equal(command, "exit"))
		return (builtin_exit(args, minienv));
	else
		return (EXIT_FAILURE);
}
