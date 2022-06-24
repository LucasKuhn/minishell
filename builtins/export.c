/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/24 19:30:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	declare_env(t_env *minienv)
{
	t_env	*aux;

	aux = minienv;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_only(aux->key_pair), STDOUT_FILENO);
		if (ft_strchr(aux->key_pair, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value_only(aux->key_pair), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	builtin_export(char **args, t_env **minienv)
{
	char	*key_pair;
	char	*varname;
	int		exit_status;

	args++;
	exit_status = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*minienv));
	while (*args)
	{
		key_pair = *args;
		varname = name_only(key_pair);
		if (!is_valid_varname(varname) || str_equal(key_pair, "="))
		{
			print_varname_error_msg("export", key_pair);
			exit_status = EXIT_FAILURE;
		}
		else if (minienv_node(varname, *minienv))
			minienv_update(varname, value_only(key_pair), *minienv);
		else
			list_append(key_pair, minienv);
		free(varname);
		args++;
	}
	return (exit_status);
}
