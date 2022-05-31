/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:51:24 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/31 13:54:33 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_varname(char c)
{
	return(ft_isalnum(c) || c == '_');
}

static char *find_var_position(char *command)
{
	while (*command)
	{
		if (*command == '\'')
		{
			command++;
			while(*command && *command != '\'')
				command++;
		}
		if (*command == '$' && is_varname(command[1]))
			return (command);
		command++;
	}
	return (NULL);
}

static char *find_exit_code_position(char *command)
{
	while (*command)
	{
		if (*command == '\'')
		{
			command++;
			while(*command && *command != '\'')
				command++;
		}
		if (*command == '$' && command[1] == '?')
			return (command);
		command++;
	}
	return (NULL);
}

void expand_exit_status(char **command, int exit_status)
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

void	expand_variable(char **command, t_env *minienv)
{
	char	*position;
	int		name_size;
	char	*var_name;
	char	*var_value;
	char	*aux1;
	char	*aux2;

	position = find_var_position(*command);
	if (position)
	{
		name_size = 1;
		while (is_varname(position[name_size]))
			name_size++;
		var_name = ft_substr(position, 1, name_size - 1);
		var_value = minienv_value(var_name, minienv);
		position[0] = '\0';
		if (!var_value)
			aux1 = ft_strjoin(*command, "");
		else
			aux1 = ft_strjoin(*command, var_value);
		aux2 = ft_strjoin(aux1, &position[name_size]);
		free(*command);
		*command = aux2;
		free(var_name);
		free(aux1);
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
