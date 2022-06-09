/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:20:51 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/09 14:44:56 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_control_c(int status)
{
	return(WTERMSIG(status) == SIGINT);
}

static int is_control_slash(int status)
{
	return(WTERMSIG(status) == SIGQUIT);
} 

static int handle_signal_interrupt(int status, int is_last_child)
{
	if (is_control_c(status))
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (is_control_slash(status) && is_last_child)
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (INTERRUPT + WTERMSIG(status));
}

int	wait_for_child(int child_pid, int is_last_child)
{
	int	status;

	if (waitpid(child_pid, &status, 0) == -1)
		exit_with_perror("waitpid", ft_itoa(child_pid), EXIT_FAILURE);
	if (WIFSIGNALED(status))
		return(handle_signal_interrupt(status, is_last_child));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(int children_pid[1024])
{
	int	i;
	int	exit_status;
	int is_last_child;

	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		is_last_child = children_pid[i+ 1] == 0;
		if (children_pid[i] != REDIRECT_FAILURE)
			exit_status = wait_for_child(children_pid[i], is_last_child);
		i++;
	}
	return (exit_status);
}
