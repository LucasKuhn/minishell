/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/01 18:38:46 by sguilher         ###   ########.fr       */
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
	handle_input_redirect(command);
	args = split_args(command);
	free(command);
	if (is_builtin(args[0]))
	{
		exit_status = execute_builtin(args, minienv);
		free_array(args);
		return (exit_status);
	}
	else
	{
		child_pid = execute_command(args, *minienv);
		free_array(args);
		redirect_fd(original_fds[0], STDIN_FILENO);
		// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
		return (wait_for_child(child_pid));
	}
}
