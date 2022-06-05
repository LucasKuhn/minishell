/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/05 19:00:42 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(char **args, t_env *minienv)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("HOME", minienv);
	if (chdir(path) != 0)
		exit_with_perror("cd", args[1], EXIT_FAILURE);
	minienv_update("OLDPWD", minienv_value("PWD", minienv), minienv);
	getcwd(cwd, PATH_MAX);
	minienv_update("PWD", cwd, minienv);
	return (EXIT_SUCCESS);
}
