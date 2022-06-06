/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:39:20 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/06 16:00:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: Adicionar um novo path e tentar executar um programa naquele path
// ex: Adicionar o minishell no path, dar um cd, e tentar executar minishell
void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return ;
}

char	*get_path(char *cmd, t_env *minienv)
{
	char	*path_env;
	char	**paths;
	char	current_path[PATH_MAX];
	int		i;

	current_path[0] = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		strs_cat(current_path, minienv_value("PWD", minienv), "/", cmd);
		//if (access(current_path, F_OK) == 0)
			return (ft_strdup(current_path));
	}
	path_env = minienv_value("PATH", minienv);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		current_path[0] = 0;
		strs_cat(current_path, paths[i], "/", cmd);
		if (access(current_path, F_OK) == 0)
		{
			ft_free_arr(paths);
			return (ft_strdup(current_path));
		}
		i++;
	}
	ft_free_arr(paths);
	return (NULL);
}

int	wait_for_child(int child_pid)
{
	int	status;

	if (child_pid == -1)
		return (EXIT_FAILURE); // TODO: Check exit_status for fork error
	if (waitpid(child_pid, &status, 0) < 0)
	{
		perror("minishell: waitpid error");
		exit(EXIT_FAILURE);
	}
	if (WIFSIGNALED(status))
	{
		// TODO: verificar o comportamento para diferentes sinais que os filhos recebem
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (INTERRUPT + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	is_folder(char *command)
{
	struct stat	statbuf;

	if (stat(command, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	execute_command(char **args, t_env *minienv)
{
	char	*path;
	int		child_pid;

	if (is_empty(args[0]))
		return (0);
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		perror("minishell : fork");
	else if (child_pid == 0)
	{
		close_extra_fds();
		if (is_folder(args[0]))
			exit_with_error(args[0], NOT_EXECUTABLE_MSG, NOT_EXECUTABLE);
		path = get_path(args[0], minienv);
		if (path == NULL)
			exit_with_error(args[0], CMD_NOT_FOUND_MSG, CMD_NOT_FOUND);
		else if (execve(path, args, minienv_to_envp(minienv)) == -1)
		{
			ft_putstr_fd("minishell: execve: ", STDERR_FILENO);
			perror(args[0]);
			if (access(path, F_OK) != 0)
				exit(CMD_NOT_FOUND);
			exit(NOT_EXECUTABLE);
		}
			// TODO: precisa retornar o errno certo!!
			// (caso do permission denied ./minishell.c)
	}
	return (child_pid);
}
