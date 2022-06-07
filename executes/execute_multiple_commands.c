/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:31 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/06 20:21:36 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(int children_pid[1024])
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		if (children_pid[i] != REDIRECT_FAILURE)
			exit_status = wait_for_child(children_pid[i]);
		i++;
	}
	return (exit_status);
}

int	execute_multiple_commands(char **commands, t_env **minienv)
{
	char	**args;
	int		original_fds[2];
	int		exit_status;
	int		children_pid[1024]; // TODO: podia ser uma lista linkada
	int		is_first_command;
	int		has_input_redirect;
	int		i;

	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	is_first_command = TRUE;
	i = 0;
	while (commands[i])
	{
		prepare_io(original_fds[1], is_first_command, (commands[i + 1] != NULL));
		is_first_command = FALSE;
		has_input_redirect = input_redirect_position(commands[i]) != NULL;
		if (has_input_redirect)
		{
			if (handle_input_redirect(commands[i]) == EXIT_FAILURE)
			{
				children_pid[i] = REDIRECT_FAILURE;
				if (commands[i + 1] == NULL)
				{
					redirect_fd(original_fds[0], STDIN_FILENO);
					return (EXIT_FAILURE);
					//precisa dar free nos comandos??
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
			children_pid[i] = execute_command(args, *minienv);
		free_array(args);
		i++;
	}
	redirect_fd(original_fds[0], STDIN_FILENO);
	children_pid[i] = 0;
	exit_status = wait_for_children(children_pid);
	return (exit_status);
}
