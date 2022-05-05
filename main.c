/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/05 15:14:54 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;
	char *prompt;
	char **args;
	
	// TODO: Tornar ENVP como global

	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		add_history(line);
		args = ft_split(line, ' ');
		if (ft_strncmp("echo", args[0], 5) == 0)
			echo(args);
		else if (ft_strncmp("pwd", args[0], 4) == 0)
			pwd(args);
		else if (ft_strncmp("env", args[0], 4) == 0)
			env(args, envp);
		else if (ft_strncmp("export", args[0], 6) == 0)
			export(args, envp);
		else if (ft_strncmp("cd", args[0], 3) == 0)
		{
			cd(args);
			prompt = get_prompt();
		}
	}
}
