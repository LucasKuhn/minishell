/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:39:20 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/23 18:38:29 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static void	handle_execve_errors(char **args, char *path, t_env *minienv)
{
	int	error;

	error = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free_array(args);
	free_minienv(&minienv);
	free(path);
	exit(error);
}

void	external_exit(char **args, t_env *minienv, int exit_status)
{
	if (exit_status == NOT_EXECUTABLE)
		print_error_msg(args[0], NOT_EXECUTABLE_MSG);
	if (exit_status == CMD_NOT_FOUND)
		print_error_msg(args[0], CMD_NOT_FOUND_MSG);
	rl_clear_history();
	free_minienv(&minienv);
	free_array(args);
	close_all_fds();
	exit(exit_status);
}

int	execute_external(char **args, t_env *minienv)
{
	char	*path;
	char	*command;

	command = args[0];
	if (is_empty(command))
		external_exit(args, minienv, EXIT_SUCCESS);
	if (is_folder(command))
		external_exit(args, minienv, NOT_EXECUTABLE);
	path = get_path(command, minienv);
	if (path == NULL)
		external_exit(args, minienv, CMD_NOT_FOUND);
	rl_clear_history();
	close_extra_fds();
	if (execve(path, args, minienv_to_envp(minienv)) == -1)
		handle_execve_errors(args, path, minienv);
	exit(EXIT_SUCCESS);
}
