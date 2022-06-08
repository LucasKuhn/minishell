/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:23:07 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/08 18:17:41 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minienv.h"

int	is_builtin(char *command);
int	cd(char **args, t_env *minienv);
int	echo(char **args);
int	pwd(void);
int	builtin_export(char **args, t_env **minienv);
int	env(t_env *envp);
int	unset(char **args, t_env **minienv);
int	builtin_exit(char **args, t_env **minienv);

// utils
int	is_varname(char c);
int	is_valid_varname(char *name);

#endif
