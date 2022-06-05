/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/05 14:54:53 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_varname(char *name)
{
	while (*name)
	{
		if (!is_varname(*name))
			return (0);
		name++;
	}
	return (1);
}

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

int	export(char **args, t_env **minienv)
{
	char	*key_pair;
	char	*varname;

	key_pair = args[1];
	if (!key_pair)
		return (declare_env(*minienv));
	varname = name_only(key_pair);
	if (!is_valid_varname(varname))
	{
		print_error_msg(varname, "not a valid identifier");
		free(varname);
		return (EXIT_FAILURE);
	}
	if (minienv_node(varname, *minienv))
		minienv_update(varname, value_only(key_pair), *minienv);
	else
		list_append(key_pair, minienv);
	return (EXIT_SUCCESS);
}
