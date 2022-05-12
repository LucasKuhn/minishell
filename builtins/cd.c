/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:03:41 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/12 15:32:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **args, t_env *minienv)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("HOME", minienv);
	if (chdir(path) == 0)
	{
		minienv_update("OLDPWD", minienv_value("PWD", minienv), minienv);
		getcwd(cwd, PATH_MAX);
		minienv_update("PWD", cwd, minienv);
	}
	else
	{
		// Good place where we may way want to use printf("%s")
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
	}
	return (0);
}