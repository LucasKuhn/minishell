/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/26 11:55:23 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	prepare_io(int fd_stdout, int is_first_command,
		int has_next_command)
{
	int			fd_in;
	int			fd_out;
	static int	fds_pipe[2];

	fd_in = STDIN_FILENO;
	if (!is_first_command)
		fd_in = fds_pipe[0];
	if (has_next_command)
	{
		if (pipe(fds_pipe) == -1)
			perror("minishell : ");
		fd_out = fds_pipe[1];
	}
	else
		fd_out = fd_stdout;
	redirect_fds(fd_in, fd_out);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;

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
		return (wait_for_child(child_pid));
	}
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	char	**args;
	int		original_fds[2];
	int		exit_status;
	int		child_pid;
	int		is_first_command;

	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	is_first_command = TRUE;

	int i = 0;
	while (commands[i])
	{
		args = split_args(commands[i]);
		prepare_io(original_fds[1], is_first_command, (commands[i + 1] != NULL));
		if (is_builtin(args[0]))
			child_pid = execute_forked_builtin(args, minienv, commands);
		else
			child_pid = execute_command(args, *minienv);
		is_first_command = FALSE;
		free_array(args);
		i++;
	}
	exit_status = wait_for_child(child_pid);
	redirect_fd(original_fds[0], STDIN_FILENO);
	return (exit_status);
}
