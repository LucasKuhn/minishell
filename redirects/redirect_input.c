/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/21 15:02:29 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *command)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_redirect_position(command, '<');
	if (!input_redirect)
		return (SUCCESS);
	file_name = get_label_name(input_redirect);
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
