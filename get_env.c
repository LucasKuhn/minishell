#include "minishell.h"

void	list_append(t_env **list, char *str)
{
	struct s_env	*new_node;
	struct s_env	*aux_node;

	new_node = malloc(sizeof(struct s_env));
	new_node->str = ft_strdup(str);
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

	list = malloc(sizeof(struct s_env));
	i = 0;
	while (envp[i])
	{
		list_append(&list, envp[i]);
		i++;
	}
	return (list);
}