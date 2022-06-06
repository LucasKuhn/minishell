/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:21:57 by coder             #+#    #+#             */
/*   Updated: 2022/06/06 15:31:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_exit_code_position(char *command)
{
	while (*command)
	{
		if (*command == '\'')
		{
			command++;
			while (*command && *command != '\'')
				command++;
		}
		if (*command == '$' && command[1] == '?')
			return (command);
		command++;
	}
	return (NULL);
}

void	expand_exit_status(char **command, int exit_status)
{
	char	*position;
	char	*exit_code_str;
	char	*aux1;
	char	*aux2;

	position = find_exit_code_position(*command);
	if (position)
	{
		exit_code_str = ft_itoa(exit_status);
		position[0] = '\0';
		aux1 = ft_strjoin(*command, exit_code_str);
		aux2 = ft_strjoin(aux1, &position[2]);
		free(*command);
		*command = aux2;
		free(exit_code_str);
		free(aux1);
		if (find_exit_code_position(*command))
			expand_exit_status(&*command, exit_status);
	}
}
