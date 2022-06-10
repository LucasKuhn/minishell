/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:12:54 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/10 17:50:26 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(char *command)
{
	char	*output_redirect;
	char	*file_name;
	int		fd;

	output_redirect = redirect_position(command, '>');
	if (!output_redirect)
		return (SUCCESS);
	file_name = redirect_file_name(output_redirect);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (SUCCESS);
}
