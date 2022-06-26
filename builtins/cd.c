/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/26 21:05:41 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "too many arguments");
	return (EXIT_FAILURE);
}

int	cd(char **args, t_env *minienv)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("__HOME", minienv);
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	pwd = minienv_value("PWD", minienv);
	oldpwd = minienv_value("OLDPWD", minienv);
	if (oldpwd && pwd && *pwd)
		minienv_update("OLDPWD", pwd, minienv);
	if (pwd && *pwd)
		minienv_update("PWD", getcwd(cwd, PATH_MAX), minienv);
	return (EXIT_SUCCESS);
}
