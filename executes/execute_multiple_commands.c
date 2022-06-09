/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 16:11:45 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (*arr)
	{
		len++;
		arr++;
	}
	return (len);
}

void	handle_pipe(int original_fd_out, char *current_command, char **commands)
{
	int			is_first_command;
	int			has_next_command;
	char		*last_command;
	static int	fds_pipe[2];
	
	last_command = commands[arr_len(commands) - 1];
	is_first_command = (current_command == commands[0]);
	has_next_command = (current_command != last_command);
	if (!is_first_command)
		redirect_fd(fds_pipe[IN], STDIN_FILENO);
	if (has_next_command)
	{
		if (pipe(fds_pipe) == -1)
			print_perror_msg("pipe", current_command);
		redirect_fd(fds_pipe[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(original_fd_out, STDOUT_FILENO);
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	char	**args;
	int		original_fds[2];
	int		exit_status;
	int		children_pid[1024]; // TODO: podia ser uma lista linkada
	int		has_input_redirect;
	int		i;

	save_original_fds(original_fds);
	i = 0;
	while (commands[i])
	{
		handle_pipe(original_fds[1], commands[i], commands);
		has_input_redirect = input_redirect_position(commands[i]) != NULL;
		if (has_input_redirect)
		{
			if (redirect_input(commands[i]) == FAILED)
			{
				children_pid[i] = REDIRECT_FAILURE;
				if (commands[i + 1] == NULL)
				{
					redirect_fd(original_fds[0], STDIN_FILENO);
					return (EXIT_FAILURE);
				}
				else
					close(STDOUT_FILENO); // para fechar o pipe de escrita
				close(STDIN_FILENO); // para fechar o pipe de leitura
				i++;
				continue;
			}
		}
		args = split_args(commands[i]);
		if (is_builtin(args[0]))
			children_pid[i] = execute_forked_builtin(args, minienv, commands);
		else
			children_pid[i] = execute_external(args, *minienv);
		free_array(args);
		i++;
	}
	redirect_fd(original_fds[0], STDIN_FILENO);
	close_extra_fds();
	children_pid[i] = 0;
	exit_status = wait_for_children(children_pid);
	return (exit_status);
}
