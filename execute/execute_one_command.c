/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:38:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/03 23:59:48 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_one_command(char *command, t_env **minienv)
{
	char	**args;
	int		child_pid;
	int		exit_status;
	int		original_fds[2];
	int		has_input_redirect;

	has_input_redirect = input_redirect_position(command) != NULL;
	if (has_input_redirect)
	{
		original_fds[0] = dup(STDIN_FILENO);
		if(handle_input_redirect(command) == EXIT_FAILURE)
		{
			free(command);
			redirect_fd(original_fds[0], STDIN_FILENO);
			return(EXIT_FAILURE);
		}
	}
	// TODO: talvez colocar a parte acima em uma função a parte
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
	free_array(args);
	if (has_input_redirect)
		redirect_fd(original_fds[0], STDIN_FILENO);
	// TODO: restore output -> redirect_fd(original_fds[1], STDOUT_FILENO);
	return (exit_status);
}
