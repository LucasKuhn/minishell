/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:15:25 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/13 15:44:14 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_name_delimeter(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t')
		return(1);
	return(0);
}

static void	move_one_forward(char *str)
{
	ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

static int	get_name_end(char *name)
{
	int	name_end;

	name_end = 0;
	while (name[name_end] && !is_name_delimeter(name[name_end]))
	{
		if (name[name_end] == '\'')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '\'')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] == '"')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '"')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] && !is_name_delimeter(name[name_end]))
			name_end++;
	}
	return (name_end);
}

char	*redirect_file_name(char *redirect_str)
{
	int		name_start;
	int		name_end;
	char	*name;
	char	*remaining_cmd;

	name_start = 1;
	if (redirect_str[name_start] == '>' || redirect_str[name_start] == '<')
		move_one_forward(&redirect_str[name_start]);
	while (redirect_str[name_start] == ' ' || redirect_str[name_start] == '\t')
		name_start++;
	name_end = get_name_end(&redirect_str[name_start]);
	name = ft_substr(&redirect_str[name_start], 0, name_end);
	remaining_cmd = &redirect_str[name_start + name_end];
	ft_memmove(redirect_str, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (name);
}
