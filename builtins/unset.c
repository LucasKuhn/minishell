/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:17 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/31 15:21:33 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(char **args, t_env **minienv)
{
	char	*name;
	t_env	*aux;
	t_env	*temp;

	name = args[1];
	if (!name)
		return (0);
	if (ft_strrchr(name, '=') != 0)
	{
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	aux = *minienv;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->key_pair, name, ft_strlen(name)) == 0)
		{
			if ((aux->next)->key_pair[ft_strlen(name)] == '=')
			{
				temp = aux->next;
				aux->next = (aux->next)->next;
				free((temp)->key_pair);
				free((temp));
				return (EXIT_SUCCESS);
			}
		}
		aux = aux->next;
	}
	return (0);
}
