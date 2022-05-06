/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/06 13:49:58 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ⚔️ 🤺
int	main(int argc, char **argv, char **envp)
{
	char *line;
	char **args;
	t_env *mini_env;
	
	mini_env = get_env(envp);
	while (1)
	{
		line = readline(get_prompt());
		add_history(line);
		args = ft_split(line, ' ');
		if (ft_strncmp("echo", args[0], 5) == 0)
			echo(args);
		else if (ft_strncmp("pwd", args[0], 4) == 0)
			pwd(args);
		else if (ft_strncmp("env", args[0], 4) == 0)
			env(args, mini_env);
		else if (ft_strncmp("export", args[0], 7) == 0)
			export(args, mini_env);
		else if (ft_strncmp("cd", args[0], 3) == 0)
			cd(args);
	}
}
