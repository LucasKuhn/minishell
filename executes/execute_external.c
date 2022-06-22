/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:39:20 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/10 14:37:53 by lalex-ku         ###   ########.fr       */
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

static void	handle_execve_errors(char **args, char *path)
{
	int	error;

	error = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	free_array(args);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	free(path);
	exit(error);
}

int	execute_external(char **args, t_env *minienv)
{
	char	*path;
	char	*command;

	command = args[0];
	if (is_empty(command))
		exit(EXIT_SUCCESS);
	if (is_folder(command))
		exit_with_error(command, NOT_EXECUTABLE_MSG, NOT_EXECUTABLE);
	path = get_path(command, minienv);
	if (path == NULL)
		exit_with_error(command, CMD_NOT_FOUND_MSG, CMD_NOT_FOUND);
	if (execve(path, args, minienv_to_envp(minienv)) == -1)
		handle_execve_errors(args, path);
	exit(EXIT_SUCCESS);
}
