/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:15:52 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/29 19:09:59 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_wildcard_label(char c)
{
	return (ft_isalnum(c) || c == '*' || c == '.' || c == '/');
}

char	*get_wildcard_label_position(char *str)
{
	char	*start;

	start = str;
	while (*str)
	{
		str += skip_quotes(str);
		if (*str == '*')
		{
			while ((str - 1) >= start && is_wildcard_label(*(str - 1)))
				str--;
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

char	*get_wildcard_label(char *wildcard_label_position)
{
	int	label_size;

	label_size = 0;
	while (is_wildcard_label(wildcard_label_position[label_size]))
		label_size++;
	return (ft_substr(wildcard_label_position, 0, label_size));
}

void	expand_wildcards(char *search, char **input, t_env *minienv)
{
	char	*wildcard_label_position;
	char	*wildcard_label;
	int		label_size;
	char	*wildcard_value;
	int		next_search_index;

	wildcard_label_position = get_wildcard_label_position(search);
	if (!wildcard_label_position)
		return ;
	wildcard_label = get_wildcard_label(wildcard_label_position);
	label_size = ft_strlen(wildcard_label);
	wildcard_value = get_wildcard_value(wildcard_label, input, minienv);
	if (*wildcard_value)
	{
		*wildcard_label_position = '\0';
		next_search_index = ft_strlen(*input);
		update_input(input, wildcard_value,
			&wildcard_label_position[label_size]);
		next_search_index += ft_strlen(wildcard_value);
		expand_wildcards(&(*input)[next_search_index], input, minienv);
	}
	else
		expand_wildcards(&wildcard_label_position[label_size], input, minienv);
	free(wildcard_value);
}
