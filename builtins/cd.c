/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/05 20:14:15 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args, t_env *minienv)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("HOME", minienv);
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	minienv_update("OLDPWD", minienv_value("PWD", minienv), minienv);
	getcwd(cwd, PATH_MAX);
	minienv_update("PWD", cwd, minienv);
	return (EXIT_SUCCESS);
}
