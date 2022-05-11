/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:39 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/11 15:40:31 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_execute_signal(int sig)
{
	(void) sig;
}

void	define_main_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL); // ctrl+C
	// sigaction(SIGQUIT, &sa, NULL); // ctrl+barra TODO: verificar se precisa mudar o comportamento no workspaces
}

void	define_execute_signals(int child_pid)
{
	struct sigaction	sa;

	if (child_pid == 0)
		sa.sa_handler = &handle_execute_signal;
	else
		sa.sa_handler = SIG_IGN; // SIG_IGN = ignorar o Ctrl+C no pai
	sigaction(SIGINT, &sa, NULL); // ctrl+C
	sigaction(SIGQUIT, &sa, NULL); // ctrl+barra - TODO: verificar no workspaces se escreve Quit
}
