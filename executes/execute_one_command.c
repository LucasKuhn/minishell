/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/21 15:01:49 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redirect(char *command, int original_fd_in)
{
	if (redirect_input(command) == FAILED)
	{
		redirect_fd(original_fd_in, STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

int	handle_output_redirect(char *command, int original_fd_out)
{
	if (redirect_output(command) == FAILED)
	{
		redirect_fd(original_fd_out, STDOUT_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

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
			if (original_fds[IN] == NO_REDIRECT)
				original_fds[IN] = dup(STDIN_FILENO);
			if (!handle_input_redirect(command, original_fds[IN]))
				return (FAILED);
		}
		if (redirect == '>')
		{
			if (original_fds[OUT] == NO_REDIRECT)
				original_fds[OUT] = dup(STDOUT_FILENO);
			if (!handle_output_redirect(command, original_fds[OUT]))
				return (FAILED);
		}
		if (redirect < 0)
		{
			if (original_fds[IN] == NO_REDIRECT)
				original_fds[IN] = dup(STDIN_FILENO);
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
	exit (EXIT_FAILURE);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	if (!handle_redirects(command, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		return (EXIT_FAILURE);
	}
	args = split_args(command);
	if (is_builtin(args[0]))
		exit_status = execute_builtin(args, minienv);
	else
		exit_status = execute_forked_external(args, *minienv);
	free_array(args);
	restore_original_fds(original_fds);
	return (exit_status);
}
