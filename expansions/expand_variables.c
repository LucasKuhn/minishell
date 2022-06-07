/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:29:20 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/07 16:31:33 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_var_position(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '$' && is_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

static void	input_update(char **input, char *var_value, char *after_var)
{
	char	*aux1;
	char	*aux2;

	if (!var_value)
		aux1 = ft_strjoin(*input, "");
	else
		aux1 = ft_strjoin(*input, var_value);
	aux2 = ft_strjoin(aux1, after_var);
	free(*input);
	*input = aux2;
	free(aux1);
}

void	expand_variables(char **input, t_env *minienv)
{
	char	*var_position;
	char	*var_name;
	char	*var_value;
	int		name_size;

	var_position = find_var_position(*input);
	if (var_position)
	{
		name_size = 1;
		while (is_varname(var_position[name_size]))
			name_size++;
		var_name = ft_substr(var_position, 1, name_size - 1);
		*var_position = '\0';
		var_value = minienv_value(var_name, minienv);
		input_update(input, var_value, (var_position + name_size));
		free(var_name);
		expand_variables(input, minienv);
	}
}
