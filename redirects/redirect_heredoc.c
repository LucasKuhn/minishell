/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:09:56 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/13 17:10:38 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect_heredoc(char *heredoc_delimeter, int original_fd_in)
{
	int		pipe_fd[2];
	int		child_pid;
	char	*line_read;
	
	if (pipe(pipe_fd) == -1)
		print_perror_msg("pipe", "HEREDOC");
	child_pid = fork();
	define_execute_signals(child_pid); // TODO: Testar se os sinais dentro do heredoc estão certos
	if (child_pid == -1)
		print_perror_msg("fork", "HEREDOC");
	else if (child_pid == 0)
	{
		close(pipe_fd[IN]);
		dup2(original_fd_in, STDIN_FILENO);
		line_read = readline("> ");
		while (!str_equal(line_read, heredoc_delimeter))
		{
			ft_putstr_fd(line_read, pipe_fd[OUT]);
			ft_putchar_fd('\n', pipe_fd[OUT]);
			line_read = readline("> ");
		}
		close(pipe_fd[OUT]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[OUT]);
		wait_for_child(child_pid, TRUE);
		redirect_fd(pipe_fd[IN], STDIN_FILENO);
	}
	return(SUCCESS);
}
