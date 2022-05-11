/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/10 19:23:00 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sign)
{
	//ft_putstr_fd("Chegamos aqui\n", 1);
	if (sign == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd("Sou o pai\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		//rl_replace_line("", 0);
	}
	// else if (sign == SIGQUIT)
	// 	exit(EXIT_SUCCESS);
	// else if (sign == SIGQUIT)
	// 	exit(EXIT_SUCCESS);
}

void	signals()
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sigaction(SIGINT, &sa, NULL); // ctrl+C
	// signal(SIGQUIT, handle_signal); // ctrl+D
	// signal(SIGQUIT, handle_signal); // ctrl+barra
}

void	handle_child_signal(int sign)
{
	if (sign == SIGINT)
	{
		dprintf(2, "oi\n");
		rl_replace_line("", 0);
		exit(142);
	}
	// else if (sign == SIGQUIT)
	// 	exit(EXIT_SUCCESS);
	// else if (sign == SIGQUIT)
	// 	exit(EXIT_SUCCESS);
}

void	child_signals(int child_pid)
{
	//struct sigaction	old_sa;
	struct sigaction	sa;

	//old_sa.sa_handler = &handle_signal;
	if (child_pid == 0)
		sa.sa_handler = &handle_child_signal;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL); // ctrl+C
}
