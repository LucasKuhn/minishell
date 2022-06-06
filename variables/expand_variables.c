/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:51:24 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/06 19:36:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_var_position(char *command)
{
	while (*command)
	{
		if (*command == '\'')
		{
			command++;
			while (*command && *command != '\'')
				command++;
		}
		if (*command == '$' && is_varname(command[1]))
			return (command);
		command++;
	}
	return (NULL);
}

static void	command_strupdate(char **command, char *var_value, char *after_var)
{
	char	*aux1;
	char	*aux2;

	if (!var_value)
		aux1 = ft_strjoin(*command, "");
	else
		aux1 = ft_strjoin(*command, var_value);
	aux2 = ft_strjoin(aux1, after_var);
	free(*command);
	*command = aux2;
	free(aux1);
}

void	expand_variable(char **command, t_env *minienv)
{
	char	*position;
	int		name_size;
	char	*var_name;
	char	*var_value;

	position = find_var_position(*command);
	if (position)
	{
		name_size = 1;
		while (is_varname(position[name_size]))
			name_size++;
		var_name = ft_substr(position, 1, name_size - 1);
		var_value = minienv_value(var_name, minienv);
		position[0] = '\0';
		command_strupdate(command, var_value, &position[name_size]);
		free(var_name);
		if (find_var_position(*command))
			expand_variable(&*command, minienv);
	}
}

void	expand_variables(char **commands, t_env *minienv, int exit_status)
{
	while (*commands)
	{
		expand_exit_status(&*commands, exit_status);
		expand_variable(&*commands, minienv);
		commands++;
	}
}
