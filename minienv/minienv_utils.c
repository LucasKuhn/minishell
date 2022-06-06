/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:28:45 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/25 13:28:46 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minienv_value(char *name, t_env *minienv)
{
	t_env	*aux;

	aux = minienv_node(name, minienv);
	if (!aux)
		return (NULL);
	return (value_only(aux->key_pair));
}

t_env	*minienv_node(char *name, t_env *minienv)
{
	t_env	*aux;
	int		size;

	aux = minienv;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->key_pair, size) == 0)
		{
			if (aux->key_pair[size] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	minienv_update(char *name, char *value, t_env *minienv)
{
	t_env	*aux;
	char	*new_keypair;
	int		size;
	int		i;

	aux = minienv_node(name, minienv);
	if (!aux)
	{
		new_keypair = create_keypair(name, value);
		list_append(new_keypair, &minienv);
		free(new_keypair);
		return ;
	}
	free(aux->key_pair);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	new_keypair = malloc(size * sizeof(char));
	i = 0;
	while (*name)
		new_keypair[i++] = *name++;
	new_keypair[i++] = '=';
	while (*value)
		new_keypair[i++] = *value++;
	new_keypair[i] = '\0';
	aux->key_pair = new_keypair;
}

size_t	minienv_size(t_env *minienv)
{
	size_t	size;
	t_env	*aux;

	size = 0;
	aux = minienv;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

char	**minienv_to_envp(t_env *minienv)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(minienv) + 1));
	aux = minienv;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->key_pair);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
