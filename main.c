/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/04/28 15:13:55 by lalex-ku         ###   ########.fr       */
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
	while (1)
	{
		line = readline(prompt);
		add_history(line);
	}
}