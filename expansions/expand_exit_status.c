/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:21:57 by coder             #+#    #+#             */
/*   Updated: 2022/06/07 16:26:20 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_exit_code_position(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

void	expand_exit_status(char **input, int exit_status)
{
	char	*position;
	char	*exit_code_str;
	char	*aux1;
	char	*aux2;

	position = find_exit_code_position(*input);
	if (position)
	{
		exit_code_str = ft_itoa(exit_status);
		position[0] = '\0';
		aux1 = ft_strjoin(*input, exit_code_str);
		aux2 = ft_strjoin(aux1, &position[2]);
		free(*input);
		*input = aux2;
		free(exit_code_str);
		free(aux1);
		expand_exit_status(input, exit_status);
	}
}
