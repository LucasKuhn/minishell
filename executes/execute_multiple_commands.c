/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 19:35:02 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

static int	handle_input_redirect(char *command, char *next_command,
		int original_fd_in)
{
	if (redirect_input(command) == FAILED)
	{
		if (next_command == NULL)
			redirect_fd(original_fd_in, STDIN_FILENO);
		else
			close(STDOUT_FILENO);
		close(STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	handle_redirects(char *command, char *next_command,
		int original_fds[2])
{
	if (has_input_redirect(command))
	{
		if (!handle_input_redirect(command, next_command, original_fds[IN]))
			return (FAILED);
	}
	return (SUCCESS);
}

static int	execute_command(char *command, char **all_commands, t_env **minienv)
{
	char	**args;
	int		child_pid;

	args = split_args(command);
	if (is_builtin(args[0]))
		child_pid = execute_forked_builtin(args, minienv, all_commands);
	else
		child_pid = execute_external(args, *minienv);
	free_array(args);
	return (child_pid);
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	int		original_fds[2];
	int		exit_status;
	int		*children_pid;
	int		*children_pid_start;
	char	**all_commands;

	save_original_fds(original_fds);
	children_pid = init_children_pid(commands);
	children_pid_start = children_pid;
	all_commands = commands;
	while (*commands)
	{
		handle_pipe(original_fds[1], *commands, all_commands);
		if (!handle_redirects(*commands, commands[1], original_fds))
		{
			if (++commands == NULL)
				return (EXIT_FAILURE);
			continue ;
		}
		*children_pid++ = execute_command(*commands, all_commands, minienv);
		commands++;
	}
	redirect_fd(original_fds[0], STDIN_FILENO);
	exit_status = wait_for_children(children_pid_start);
	clean_after_execute(children_pid_start);
	return (exit_status);
}
