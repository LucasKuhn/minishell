/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:29:52 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/03 23:57:52 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_extra_fds()
{
	int	last_open_fd;
	int	fd;

	// TODO: melhorar isso aqui!!
	last_open_fd = open("minishell.h", O_RDONLY, FD_CLOEXEC);
	if (last_open_fd == -1)
		return ; // não sei se isso é bom
	fd = 3;
	while (fd <= last_open_fd)
	{
		close(fd);
		fd++;
	}
}

void	close_all_fds()
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close_extra_fds();
}
