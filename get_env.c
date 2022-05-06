#include "minishell.h"
#include <stdio.h>

void	list_append(char *key_pair, t_env **list)
{
	struct s_env	*new_node;
	struct s_env	*aux_node;

	new_node = malloc(sizeof(struct s_env));
	new_node->key_pair = ft_strdup(key_pair);
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	aux_node = *list;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}

t_env *get_env(char **envp)
{
	t_env *list;
	int i;

	//list = malloc(sizeof(struct s_env));
	list = NULL;
	i = 0;
	while (envp[i])
	{
		list_append(envp[i], &list);
		i++;
	}
	return (list);
}

char	*var_name(char *key_pair)
{
	int i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (ft_substr(key_pair, 0, i));
}

char	*var_value(char *key_pair)
{
	int i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i+1]);
}

// TODO:
t_env	*get_minienv(char *name, t_env *minienv)
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
