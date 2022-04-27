/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/04/27 17:05:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#include <readline/readline.h> // readline 
#include <stdlib.h> // getenv
#include <unistd.h> // getwd ttyname
int	main()
{
	char *line; 
	char *user; 
	char *cwd; 

	getcwd(cwd, 1024);
	user = getenv("USER");
	
	HIST_ENTRY **h;
	h=history_get(1);
	
	while (1)
	{
		printf(GRN"%s"WHT"@"MAG"%s"CRESET, user, cwd); 
		line = readline(" > ");
		add_history(line);
	}
}
