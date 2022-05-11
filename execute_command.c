/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:39:20 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/11 01:02:15 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Adicionar um novo path e tentar executar um programa naquele path
// ex: Adicionar o minishell no path, dar um cd, e tentar executar minishell
void	ft_free_arr(char	**arr)
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

char *get_executable(char *cmd, t_env *minienv)
{
	char *path_env;
	char **paths;
	char current_path[PATH_MAX];
	int	i;

	current_path[0] = 0;
	strs_cat(current_path, minienv_value("PWD", minienv), "/", cmd);
	if (access(current_path, X_OK) == 0)
		return (ft_strdup(current_path));
	path_env = minienv_value("PATH", minienv);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		current_path[0] = 0;
		strs_cat(current_path, paths[i], "/", cmd);
		if (access(current_path, X_OK) == 0)
		{
			ft_free_arr(paths);
			return (ft_strdup(current_path));
		}
		i++;
	}
	ft_free_arr(paths);
	return(NULL);
}

void execute_command(char **args, t_env *minienv)
{
	char *path;
	int child_pid;
	int result;
	int	status;

	child_pid = fork();
	child_signals(child_pid);
	rl_replace_line("", 0);
	if (child_pid == -1) // problema no fork
		ft_putstr_fd("minishell: fork creating error\n", STDERR_FILENO);
	else if (child_pid == 0) // se for o filho
	{
		path = get_executable(args[0], minienv);
		result = execve(path, args, minienv_to_envp(minienv));
		ft_putstr_fd("minishell: ", STDERR_FILENO); // TODO: Colocar em uma aux (ex: exit_with_message)
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("Esperando o filho...\n", 1);
		// sleep(3);
		// kill(child_pid, SIGKILL); // o kill manda um SIGKILL (= 9) para o filho
		// e o filho acaba sendo interrompido e envia o status = 9 (WIFEXITED também não retorna true)
		if (waitpid(child_pid, &status, 0) < 0)
		{
			perror("minishell: waitpid error");
			exit(EXIT_FAILURE);
		}
		printf("status do filho 1: %i\n", status);
		if (WIFEXITED(status))
			printf("status do filho 2: %i\n", WEXITSTATUS(status));
		ft_putstr_fd("O filho terminou\n", 1);
		signals();
	}
}
