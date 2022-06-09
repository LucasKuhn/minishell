/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:20:51 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/08 18:21:52 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_child(int child_pid)
{
	int	status;

	if (child_pid == -1)
		return (EXIT_FAILURE); // TODO: Check exit_status for fork error
	if (waitpid(child_pid, &status, 0) < 0)
	{
		perror("minishell: waitpid error");
		exit(EXIT_FAILURE);
	}
	if (WIFSIGNALED(status))
	{
		// TODO: verificar o comportamento para diferentes sinais que os filhos recebem
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (INTERRUPT + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(int children_pid[1024])
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		if (children_pid[i] != REDIRECT_FAILURE)
			exit_status = wait_for_child(children_pid[i]);
		i++;
	}
	if (is_quit(exit_status))
		print_quit();
	return (exit_status);
}
