/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/06 16:58:13 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		print_varname_error_msg("export", varname);
		free(varname);
		return (EXIT_FAILURE);
	}
	if (minienv_node(varname, *minienv))
		minienv_update(varname, value_only(key_pair), *minienv);
	else
		list_append(key_pair, minienv);
	return (EXIT_SUCCESS);
}
// TODO: implementar multiplos exports
// export UM=1 DOIS-2 TRES=3
// mesmo dando erro no segundo, cria as duas outras variáveis
// exit code = 1
