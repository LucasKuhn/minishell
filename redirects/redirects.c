/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:55:26 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/01 18:45:04 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_io(int fd_stdout, int is_first_command,
		int has_next_command)
{
	int			fd_in;
	int			fd_out;
	static int	fds_pipe[2];

	fd_in = STDIN_FILENO;
	if (!is_first_command)
		fd_in = fds_pipe[0];
	if (has_next_command)
	{
		if (pipe(fds_pipe) == -1)
			perror("minishell : ");
		fd_out = fds_pipe[1];
	}
	else
		fd_out = fd_stdout;
	redirect_fds(fd_in, fd_out);
}

void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}

void	redirect_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		redirect_fd(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		redirect_fd(fd_out, STDOUT_FILENO);
}
