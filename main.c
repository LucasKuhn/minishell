/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/04/27 19:21:49 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main()
{
	char *line; 
	char *user; 
	char *cwd; 

	getcwd(cwd, 1024);
	user = getenv("USER");
	
	char *prompt;
	// prompt = get_prompt(); 
	
	// while (1)
	// {
	// 	printf(GRN"%s"WHT"@"MAG"%s"CRESET, user, prompt); 
	// 	line = readline(" > ");
	// 	add_history(line);
	// }
}