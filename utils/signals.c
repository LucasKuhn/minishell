/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/25 14:22:01 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	define_main_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL); // ctrl+C
}

static void	handle_execute_signal(int sig)
{
	(void)sig;
}

void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	if (child_pid == 0)
		sa.sa_handler = &handle_execute_signal;
	else
		sa.sa_handler = SIG_IGN; // SIG_IGN = ignorar o Ctrl+C no pai
	sigaction(SIGINT, &sa, NULL); // ctrl+C
	sigaction(SIGQUIT, &sa, NULL); // ctrl+barra 
	// TODO: verificar no workspaces se escreve Quit
}
