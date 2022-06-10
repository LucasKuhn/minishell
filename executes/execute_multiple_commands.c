/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/10 14:38:13 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

static void	handle_input_redirect(char *command, char *next_command,
		int original_fd_in)
{
	if (redirect_input(command) == FAILED)
	{
		if (next_command == NULL)
			redirect_fd(original_fd_in, STDIN_FILENO);
		else
			close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit (EXIT_FAILURE);
	}
}

static void	handle_redirects(char *command, char *next_command,
		int original_fds[2])
{
	if (has_input_redirect(command))
		handle_input_redirect(command, next_command, original_fds[IN]);
}

static void	execute_forked_command(char *command, char **all_commands, t_env **minienv)
{
	char	**args;

	close_extra_fds();
	args = split_args(command);
	if (is_builtin(args[0]))
		execute_forked_builtin(args, minienv, all_commands);
	else
		execute_external(args, *minienv);
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	int	original_fds[2];
	int	*children_pid;
	int	exit_status;
	int	i;

	save_original_fds(original_fds);
	children_pid = init_children_pid(commands);
	i = 0;
	while (commands[i])
	{
		handle_pipe(original_fds[OUT], commands[i], commands);
		children_pid[i] = fork();
		define_execute_signals(children_pid[i]);
		if (children_pid[i] == -1)
			print_perror_msg("fork", commands[i]);
		else if (children_pid[i] == 0)
		{
			handle_redirects(commands[i], commands[1], original_fds);
			execute_forked_command(commands[i], commands, minienv);
		}
		i++;
	}
	redirect_fd(original_fds[IN], STDIN_FILENO);
	exit_status = wait_for_children(children_pid);
	return (exit_status);
}
