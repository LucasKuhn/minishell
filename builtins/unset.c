/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:17 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/06 16:55:53 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minienv_del_next_node(t_env **node);

int	unset(char **args, t_env **minienv)
{
	char	*varname;
	t_env	*aux;

	varname = args[1];
	if (!varname)
		return (0);
	if (!is_valid_varname(varname))
	{
		print_varname_error_msg("unset", varname);
		return (EXIT_FAILURE);
	}
	aux = *minienv;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->key_pair, varname, ft_strlen(varname)) == 0)
		{
			if ((aux->next)->key_pair[ft_strlen(varname)] == '=')
				return (minienv_del_next_node(&aux));
		}
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}
// TODO: implementar multiplos unsets
// unset UM=1 DOIS-2 TRES=3
// exit code = 1
// mesmo dando erro no segundo, apaga as duas outras variáveis

static int	minienv_del_next_node(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->key_pair);
	free(temp);
	return (EXIT_SUCCESS);
}
