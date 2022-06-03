/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/03 19:15:22 by sguilher         ###   ########.fr       */
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
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = 0; // TODO: Entender o que essa flag faz
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL); // ctrl+C
	sa_sigquit.sa_handler = SIG_IGN; // Ctr+barra não pode fazer nada
	sa_sigquit.sa_flags = 0; // TODO: Entender o que essa flag faz
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_sigquit, NULL); // ctrl+barra
}

void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0; // TODO: Entender o que essa flag faz
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN; // SIG_IGN = ignorar o Ctrl+C e o Ctrl+barra no pai
	sigaction(SIGINT, &sa, NULL); // ctrl+C
	sigaction(SIGQUIT, &sa, NULL); // ctrl+\ TODO: verificar no workspaces se escreve Quit
}
