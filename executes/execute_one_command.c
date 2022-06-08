/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/08 16:29:26 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_input_redirect(char *command)
{
	return (input_redirect_position(command) != NULL);
}

int	handle_input_redirect(char *command, int *original_fd_in)
{
	*original_fd_in = dup(STDIN_FILENO);
	if (redirect_input(command) == FAILED)
	{
		redirect_fd(*original_fd_in, STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	handle_redirects(char *command, int *original_fd_in)
{
	*original_fd_in = NO_REDIRECT;
	if (has_input_redirect(command))
	{
		if (!handle_input_redirect(command,original_fd_in))
			return (FAILED);
	}
	// TODO: handle output -> original_fds[1] = dup(STDOUT_FILENO);
	return (SUCCESS);
}

static void	restore_std_fds(int original_fd_in)//, int original_out_fd)
{
	if (original_fd_in != NO_REDIRECT)
		redirect_fd(original_fd_in, STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;
	int		original_fds[2];

	if (!handle_redirects(command, &original_fds[0]))
		return (EXIT_FAILURE);
	args = split_args(command);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, minienv);
	else
	{
		child_pid = execute_command(args, *minienv);
		exit_status = wait_for_child(child_pid);
		if (is_quit(exit_status))
			print_quit();
	}
	free_array(args);
	restore_std_fds(original_fds[0]);
	return (exit_status);
}
