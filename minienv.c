#include "minishell.h"

t_env	*init_minienv(char **envp)
{
	t_env *list;
	int i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		list_append(envp[i], &list);
		i++;
	}
	return (list);
}

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
