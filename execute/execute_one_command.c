/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:08 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;
	int		original_fds[2];

	original_fds[0] = dup(STDIN_FILENO);
	// TODO: handle output -> original_fds[1] = dup(STDOUT_FILENO);
	if(handle_input_redirect(command) == EXIT_FAILURE)
	{
		free(command);
		redirect_fd(original_fds[0], STDIN_FILENO);
		return(EXIT_FAILURE);
	}
	args = split_args(command);
	free(command);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, minienv);
	else
	{
		child_pid = execute_command(args, *minienv);
		exit_status = wait_for_child(child_pid);
	}
	free_array(args);
	redirect_fd(original_fds[0], STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
	return (exit_status);
}
