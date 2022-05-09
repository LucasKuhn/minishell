/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/08 23:22:19 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int str_equal(const char* str1, const char* str2)
{
	int size;
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return 0;
	return (ft_strncmp(str1, str2, size) == 0);
}

int	main(int argc, char **argv, char **envp)
{
	char *input;
	char **args;
	char *command;
	t_env *minienv;

	minienv = init_minienv(envp);
	while (1)
	{
		input = prompt_input(minienv);
		args = ft_split(input, ' ');
		command = args[0];
		if (!command)
			continue; // TODO: verificar se pode usar
		if (str_equal(command, "echo"))
			echo(args);
		else if (str_equal(command, "pwd"))
			pwd(args);
		else if (str_equal(command, "env"))
			env(args, minienv);
		else if (str_equal(command, "export"))
			export(args, &minienv);
		else if (str_equal(command, "cd"))
			cd(args, minienv);
	}
}
