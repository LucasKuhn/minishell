/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/24 18:47:59 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_variable(char **command, t_env *minienv)
{
	char	*position;
	int		name_size;
	char	*var_name;
	char	*var_value;
	char	*aux1;
	char	*aux2;

	position = ft_strchr(*command, '$');
	if (position)
	{
		name_size = 1;
		while (position[name_size] && position[name_size] != ' ')
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
	}
	if (ft_strchr(*command, '$'))
		expand_variable(&*command, minienv);
}

void expand_variables(char **commands, t_env *minienv)
{
	while (*commands)
	{
		expand_variable(&*commands, minienv);
		commands++;
	}
}

int is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int minishell(t_env	*minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = 0;
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!*input || has_unclosed_quotes(input) || is_empty(input))
			continue;
		// TODO: check syntax before splitting
		commands = split_commands(input); //TODO: limpar commands
		expand_variables(commands, minienv);
		if (commands[1] == NULL)
			exit_status = execute_one_command(commands[0], &minienv);
		else
			exit_status = execute_multiple_commands(commands, &minienv);
	}
	return (exit_status);
}
