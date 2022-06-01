/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:04:06 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/01 11:10:59 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO: Conferir o que o export deve fazer quando não recebe nada
int	is_valid_varname(char *name)
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
		ft_putstr_fd(aux->key_pair, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

void	print_export_error_msg(char *varname, char *msg)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(varname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	export(char **args, t_env **minienv)
{
	char	*key_pair;
	char	*name;
	int		size;
	t_env	*aux;

	key_pair = args[1]; // TODO: implementar quando tem arg[2] ou mais
	if (!key_pair)
		return (declare_env(*minienv));
	// TODO: Daria pra fazer uma aux que recebe o tamanho do nome
	name = name_only(key_pair);
	if (name == NULL)
		return (0); // TODO: Checar esse retorno
	if (!is_valid_varname(name))
	{
		print_export_error_msg(name, "not a valid identifier");
		free(name);
		return (EXIT_FAILURE);
	}
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
