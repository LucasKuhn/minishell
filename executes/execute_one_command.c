/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/07 14:24:23 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(char *command) // melhorar o nome da função
{
	int	has_input_redirect;
	int	original_in_fd;

	has_input_redirect = input_redirect_position(command) != NULL;
	if (has_input_redirect)
	{
		original_in_fd = dup(STDIN_FILENO);
		if (handle_input_redirect(command) == EXIT_FAILURE)
		{
			free(command);
			redirect_fd(original_in_fd, STDIN_FILENO);
			return (REDIRECT_FAILURE);
		}
		return (original_in_fd);
	}
	else
		return (NO_REDIRECT);
}

static void	restore_fds(int original_in_fd)//, int original_out_fd)
{
	if (original_in_fd != NO_REDIRECT)
		redirect_fd(original_in_fd, STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;
	int		original_fds[2];

	original_fds[0] = redirect_input(command);
	if (original_fds[0] == REDIRECT_FAILURE)
		return (EXIT_FAILURE);
	// TODO: handle output -> original_fds[1] = dup(STDOUT_FILENO);
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
	restore_fds(original_fds[0]);
	return (exit_status);
}