/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/13 17:09:52 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *command, int original_fd_in)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;


	input_redirect = redirect_position(command, '<');
	if (!input_redirect)
		return (SUCCESS);
	if (input_redirect[1] == '<')
	{
		file_name = redirect_file_name(input_redirect);
		return(redirect_heredoc(file_name, original_fd_in));
	}
	file_name = redirect_file_name(input_redirect);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}
