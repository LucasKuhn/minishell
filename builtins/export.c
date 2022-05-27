/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/25 13:15:46 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: Conferir o que o export deve fazer quando não recebe nada
static int	declare_env(t_env *minienv)
{
	t_env	*aux;

	aux = minienv;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(aux->key_pair, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	export(char **args, t_env **minienv)
{
	char	*key_pair;
	char	*name;
	int		size;
	t_env	*aux;

	key_pair = args[1];
	if (!key_pair)
		return (declare_env(*minienv));
	// TODO: Daria pra fazer uma aux que recebe o tamanho do nome
	name = name_only(key_pair); 
	if (name == NULL)
		return (0); // TODO: Checar esse retorno
	aux = *minienv;
	size = ft_strlen(name) + 1;
	free(name);
	while (aux)
	{
		if (ft_strncmp(aux->key_pair, key_pair, size) == 0)
		{
			free(aux->key_pair);
			aux->key_pair = ft_strdup(key_pair);
			return (0); // TODO: Checar esse retorno
		}
		aux = aux->next;
	}
	list_append(key_pair, minienv);
	return (0);
}
