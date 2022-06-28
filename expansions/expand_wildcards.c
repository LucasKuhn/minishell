/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:15:52 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/27 21:03:23 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wildcard_label_position(char *str)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '*')
		{
			while (*str != ' ' && str > start) // verificar que provavelmente não é só espaço
				str--;
			if (*str == ' ')
				str++;
			return (str);
		}
		str++;
	}
	return (NULL);
}

void	update_input(char **input, char *wildcard_value, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	if (!*input[0] && !wildcard_value)
		first_part = ft_strdup("");
	else if (!*input[0] && wildcard_value)
		first_part = ft_strdup(wildcard_value);
	else if (!wildcard_value)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, wildcard_value);
	updated_input = ft_strjoin(first_part, second_part);
	free(first_part);
	free(*input);
	*input = updated_input;
}

void	remove_new_lines(char *wildcard_value)
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

char	**get_args(char *wildcard_label)
{
	char	**args;

	args = malloc(sizeof(char *) * 11);
	args[0] = "find";
	args[1] = ".";
	args[2] = "-maxdepth";
	args[3] = "1";
	args[4] = "-name";
	args[5] = wildcard_label;
	args[6] = "-exec";
	args[7] = "basename";
	args[8] = "{}";
	args[9] = ";";
	args[10] = NULL;
	return (args);
}

void	expand_wildcards(char **input, t_env *minienv)
{
	char	*wildcard_label_position;
	char	wildcard_value[4096];
	int		child_pid;
	int		pipe_fds[2];
	char	*second_part;
	char	*wildcard_label;
	int		label_size;
	char	**envp;

	//echo 'bye *' t*.c bye
	wildcard_label_position = get_wildcard_label_position(*input);
	if (!wildcard_label_position)
		return ;
	label_size = 0;
	while (wildcard_label_position[label_size + 1] && wildcard_label_position[label_size + 1] != ' ')
		label_size++;
	wildcard_label = ft_substr(wildcard_label_position, 0, label_size + 1);
	printf("wildcard_label = |%s|\n", wildcard_label);
	*wildcard_label_position = '\0';
	second_part = &wildcard_label_position[label_size + 1];
	printf("first_part = |%s|\n", *input);
	printf("wildcard_label = |%s|\n", wildcard_label);
	printf("second_part = |%s|\n", second_part);
	pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == -1)
		print_perror_msg("fork", "wildcard");
	if (child_pid == 0)
	{
		rl_clear_history();
		envp = minienv_to_envp(minienv);
		free_minienv(&minienv);
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
		if (execve("/usr/bin/find", get_args(wildcard_label), envp) == -1)
		{
			printf("deu pau\n");
			exit(1);
		}
	}
	else
	{
		free(wildcard_label);
		close(pipe_fds[1]);
		waitpid(child_pid, NULL, 0);
		ft_bzero(wildcard_value, sizeof(wildcard_value));
		read(pipe_fds[0], wildcard_value, sizeof(wildcard_value));
		remove_new_lines(wildcard_value);
		//printf("filho terminou\n");
		//printf("wildcard_value = |%s|\n", wildcard_value);
		printf("before update = |%s|\n", *input);
		wildcard_label_position[label_size] = '\0';
		update_input(input, wildcard_value, second_part);
		printf("after update = |%s|\n", *input);
	}
	expand_wildcards(input, minienv);
}

// *.c X
// test*.c
// echo test*.c
// echo 'bye *' test*.c bye
// echo 'bye *' mini* bye
// echo *
// echo "*"
// "*"
// test*
// *
// <*.txt
