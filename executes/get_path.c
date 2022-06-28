/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:15:41 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/28 13:49:17 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_path(char base[], char *part1, char *part2, char *part3)
{
	*base = 0;
	ft_strlcat(base, part1, PATH_MAX);
	ft_strlcat(base, part2, PATH_MAX);
	ft_strlcat(base, part3, PATH_MAX);
}

static int	is_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (TRUE);
	return (FALSE);
}

static char	*local_path(char *command, t_env *minienv)
{
	char	full_path[PATH_MAX];

	if (*command == '/')
		return (ft_strdup(command));
	full_path[0] = 0;
	create_path(full_path, minienv_value("PWD", minienv), "/", command);
	return (ft_strdup(full_path));
}

char	*get_path(char *command, t_env *minienv)
{
	char	*path_env;
	char	**paths;
	char	current_path[PATH_MAX];
	char	**paths_start;

	if (is_path(command))
		return (local_path(command, minienv));
	path_env = minienv_value("PATH", minienv);
	paths = ft_split(path_env, ':');
	paths_start = paths;
	while (paths && *paths)
	{
		create_path(current_path, *paths, "/", command);
		if (access(current_path, F_OK) == 0)
		{
			free_array(paths_start);
			return (ft_strdup(current_path));
		}
		paths++;
	}
	free_array(paths_start);
	return (NULL);
}
