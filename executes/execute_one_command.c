/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/07 18:44:05 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirect(char *command, int *original_fd_in) // melhorar o nome da função
{
	int	has_input_redirect;

	has_input_redirect = input_redirect_position(command) != NULL;
	if (has_input_redirect)
	{
		*original_fd_in = dup(STDIN_FILENO);
		return(redirect_input(command));
	}
	return (EXIT_SUCCESS);
}

static void	restore_std_fds(int original_fd_in)//, int original_out_fd)
{
	if (original_fd_in != NO_REDIRECT)
		redirect_fd(original_fd_in, STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
}

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;
	int		original_fds[2];

	original_fds[0] = NO_REDIRECT;
	if (handle_input_redirect(command, &original_fds[0]) == EXIT_FAILURE)
	{
		dup2(original_fds[0], STDIN_FILENO);
		return (EXIT_FAILURE);
	}
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
	if (exit_status == (INTERRUPT + SIGQUIT))
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	free_array(args);
	restore_std_fds(original_fds[0]);
	close_extra_fds();
	return (exit_status);
}
