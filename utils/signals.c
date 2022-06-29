/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/28 18:51:09 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	define_main_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
