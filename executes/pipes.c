/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:35:24 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 19:37:17 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(int original_fd_out, char *current_command, char **commands)
{
	int			is_first_command;
	int			has_next_command;
	char		*last_command;
	static int	fds_pipe[2];

	last_command = commands[arr_len(commands) - 1];
	is_first_command = (current_command == commands[0]);
	has_next_command = (current_command != last_command);
	if (!is_first_command)
		redirect_fd(fds_pipe[IN], STDIN_FILENO);
	if (has_next_command)
	{
		if (pipe(fds_pipe) == -1)
			print_perror_msg("pipe", current_command);
		redirect_fd(fds_pipe[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(original_fd_out, STDOUT_FILENO);
}
