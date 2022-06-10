/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/10 14:23:46 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!handle_input_redirect(command, original_fd_in))
			return (FAILED);
	}
	// TODO: handle output -> original_fds[1] = dup(STDOUT_FILENO);
	return (SUCCESS);
}

static void	restore_std_fds(int original_fd_in) //, int original_out_fd)
{
	if (original_fd_in != NO_REDIRECT)
		redirect_fd(original_fd_in, STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
}

int	execute_forked_external(char **args, t_env *minienv)
{
	int		child_pid;
	char	*command;

	command = args[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", command);
	else if (child_pid == 0)
		execute_external(args, minienv);
	else
		return (wait_for_child(child_pid, TRUE));
	exit (EXIT_FAILURE);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	if (!handle_redirects(command, &original_fds[0]))
		return (EXIT_FAILURE);
	args = split_args(command);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, minienv);
	else
		exit_status = execute_forked_external(args, *minienv);
	free_array(args);
	restore_std_fds(original_fds[0]);
	return (exit_status);
}
