/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_value_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:33:48 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/28 18:55:22 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	remove_new_lines(char *wildcard_value)
{
	while (*wildcard_value)
	{
		if (*wildcard_value == '\n' && wildcard_value[1])
			*wildcard_value = ' ';
		else if (*wildcard_value == '\n')
			*wildcard_value = '\0';
		wildcard_value++;
	}
}

static char	**get_args(char *wildcard_label)
{
	char	**args;

	args = malloc(sizeof(char *) * 11);
	args[0] = "find";
	args[1] = ".";
	args[2] = "-maxdepth";
	args[3] = "1";
	args[4] = "-name";
	if (str_equal(wildcard_label, "*"))
		args[5] = "[!.]*";
	else
		args[5] = wildcard_label;
	args[6] = "-exec";
	args[7] = "basename";
	args[8] = "{}";
	args[9] = ";";
	args[10] = NULL;
	return (args);
}

static void	execute_find(char *wildcard_label, int pipe_fds[2], t_env *minienv)
{
	char	**envp;

	rl_clear_history();
	envp = minienv_to_envp(minienv);
	free_minienv(&minienv);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	if (execve("/usr/bin/find", get_args(wildcard_label), envp) == -1)
		exit(EXIT_FAILURE);
}

char	*get_wildcard_value(char *wildcard_label, char **input, t_env *minienv)
{
	int		child_pid;
	int		pipe_fds[2];
	char	wildcard_value[4096];

	pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == -1)
		print_perror_msg("fork", "wildcard");
	if (child_pid == 0)
	{
		free(*input);
		execute_find(wildcard_label, pipe_fds, minienv);
	}
	free(wildcard_label);
	close(pipe_fds[1]);
	waitpid(child_pid, NULL, 0);
	ft_bzero(wildcard_value, sizeof(wildcard_value));
	read(pipe_fds[0], wildcard_value, sizeof(wildcard_value));
	close(pipe_fds[0]);
	remove_new_lines(wildcard_value);
	return (ft_strdup(wildcard_value));
}
