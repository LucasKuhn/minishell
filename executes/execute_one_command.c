/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/24 10:36:46 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirects(char *command, int original_fds[2])
{
	char	redirect;

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	redirect = get_next_redirect(command);
	while (redirect)
	{
		if (redirect == '<')
		{
			if (!handle_input_redirect(command, original_fds))
				return (FAILED);
		}
		if (redirect == '>')
		{
			if (!handle_output_redirect(command, original_fds))
				return (FAILED);
		}
		if (redirect < 0)
		{
			save_original_fd_in(original_fds);
			redirect_heredoc(command, redirect);
		}
		redirect = get_next_redirect(command);
	}
	return (SUCCESS);
}

static void	restore_original_fds(int original_fds[2])
{
	if (original_fds[IN] != NO_REDIRECT)
		redirect_fd(original_fds[IN], STDIN_FILENO);
	if (original_fds[OUT] != NO_REDIRECT)
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
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
	exit(EXIT_FAILURE);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	if (!handle_redirects(command, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		free(command);
		return (EXIT_FAILURE);
	}
	args = split_args(command);
	free(command);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, minienv);
	else
		exit_status = execute_forked_external(args, *minienv);
	free_array(args);
	restore_original_fds(original_fds);
	return (exit_status);
}
