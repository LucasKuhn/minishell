/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:29:54 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/12 16:45:20 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_pipes(char *str, char delimeter);
static void	restore_pipes(char **exec_args);
static int	contains_pipe(char *str);

char	**split_commands(char *input)
{
	char	**commands;

	if (!contains_pipe(input))
	{
		commands = malloc(2 * sizeof(char *));
		commands[0] = ft_strdup(input);
		commands[1] = NULL;
		return (commands);
	}
	replace_pipes(input, '"');
	replace_pipes(input, '\'');
	commands = ft_split(input, '|');
	restore_pipes(commands);
	return (commands);
}

static int	contains_pipe(char *str)
{
	while (*str)
	{
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

static void	replace_pipes(char *str, char delimeter)
{
	while (*str && *str != delimeter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimeter)
	{
		if (*str == '|')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_pipes(str, delimeter);
}

static void	restore_pipes(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = '|';
			str++;
		}
		exec_args++;
	}
	return ;
}
