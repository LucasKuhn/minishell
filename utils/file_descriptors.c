/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:29:52 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/06 15:30:41 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_extra_fds(void)
{
	int	last_open_fd;
	int	fd;

	last_open_fd = open("minishell.h", O_RDONLY, FD_CLOEXEC);
	if (last_open_fd == -1)
	{
		last_open_fd = open("minishell.h", O_RDONLY, FD_CLOEXEC);
		if (last_open_fd == -1)
			print_error_msg("close", "error closing extra file descriptors");
		// é uma boa mensagem? é uma boa abordagem tentar abrir mais uma vez?
		// melhor referenciar o close ou o open?
		// qdo pode dar problema: se tiver aberto o máximo de fds
	}
	fd = 3;
	while (fd <= last_open_fd)
	{
		close(fd);
		fd++;
	}
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
