/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:16 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/12 15:26:11 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env **minienv)
{
	char *builtin_strs[7];
	int i;
	
	builtin_strs[0] = "echo";
	builtin_strs[1] = "cd";
	builtin_strs[2] = "pwd";
	builtin_strs[3] = "export";
	builtin_strs[4] = "unset";
	builtin_strs[5] = "env";
	builtin_strs[6] = "exit";

	int (*builtin_func[7]) (char **, t_env**);
	builtin_func[0] = &echo;
	builtin_func[1] = &cd;
	builtin_func[2] = &pwd;
	builtin_func[3] = &export;
	builtin_func[4] = &unset;
	builtin_func[5] = &env;
	builtin_func[6] = &builtin_exit;

	i = 0;
	while(i < 7)
	{
		if(str_equal(args[0], builtin_strs[i]))
			return (*builtin_func[i])(args, minienv);
		i++;
	}
	return(0);
}