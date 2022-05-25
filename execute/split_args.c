/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:19:32 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/11 17:42:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_spaces(char *str, char delimeter);
void	restore_spaces(char **exec_args);
int		contains_quote_mark(char *str);
void	remove_quotes(char *str);

char	**split_args(char *command)
{
	char	**exec_args;

	if (!contains_quote_mark(command))
		return (ft_split(command, ' '));
	replace_spaces(command, '"');
	replace_spaces(command, '\'');
	remove_quotes(command);
	exec_args = ft_split(command, ' ');
	restore_spaces(exec_args);
	return (exec_args);
}

void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

void	remove_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		str++;
	}
}

void	replace_spaces(char *str, char delimeter)
{
	while (*str && *str != delimeter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimeter)
	{
		if (*str == ' ')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_spaces(str, delimeter);
}

int	contains_quote_mark(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}
