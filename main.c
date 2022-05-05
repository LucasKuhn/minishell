/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/04 22:13:28 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *line;
	char *prompt;
	char **args;

	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt);
		add_history(line);
		args = ft_split(line, ' ');
		if (ft_strncmp("echo", args[0], 5) == 0)
			echo(&args[1]);
	}
}
