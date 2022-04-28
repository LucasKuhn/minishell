/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/04/28 11:10:38 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#include <string.h>

int	main()
{
	char *line;
	char *prompt;
	prompt = get_prompt(); 
	
	char *str;
	str = malloc(sizeof(char) * 512);
	strlcat(str,"\001\e[0;32m\002lucas\001\e[0m\002 > ", 99);
	printf("here -> %s\n", str);

	// strlcat(str,"---------------------------------------------> ", 99);
	while (1)
	{
		line = readline(str);
		add_history(line);
	}
}