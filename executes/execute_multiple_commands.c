/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 17:03:51 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void save_original_fds(int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
}

static int handle_input_redirect(char *command, char *next_command, int original_fd_in, int *child_pid)
{
	if (redirect_input(command) == FAILED)
	{
		*child_pid = REDIRECT_FAILURE;
		if (next_command == NULL)
			redirect_fd(original_fd_in, STDIN_FILENO);
		else
			close(STDOUT_FILENO); // para fechar o pipe de escrita
		close(STDIN_FILENO); // para fechar o pipe de leitura
		return (FAILED);
	}
	return (SUCCESS);
}

static int handle_redirects(char *command, char *next_command, int original_fds[2], int *child_pid)
{
	if (has_input_redirect(command))
	{
		if (!handle_input_redirect(command, next_command, original_fds[IN], child_pid))
			return (FAILED);
	}
	return (SUCCESS);
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	char	**args;
	int		original_fds[2];
	int		exit_status;
	int		children_pid[1024]; // TODO: podia ser uma lista linkada
	int		i;

	save_original_fds(original_fds);
	i = 0;
	while (commands[i])
	{
		handle_pipe(original_fds[1], commands[i], commands);
		if (!handle_redirects(commands[i], commands[i + 1], original_fds, &children_pid[i]))
		{
			if (commands[i + 1] == NULL)
				return (EXIT_FAILURE);
			i++;
			continue;
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
