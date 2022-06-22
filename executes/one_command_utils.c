/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:58:26 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/22 16:06:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_original_fd_in(int original_fds[2])
{
	if (original_fds[IN] == NO_REDIRECT)
		original_fds[IN] = dup(STDIN_FILENO);
}

void	save_original_fd_out(int original_fds[2])
{
	if (original_fds[OUT] == NO_REDIRECT)
		original_fds[OUT] = dup(STDOUT_FILENO);
}

int	handle_input_redirect(char *command, int original_fds[2])
{
	save_original_fd_in(original_fds);
	if (redirect_input(command) == FAILED)
	{
		redirect_fd(original_fds[IN], STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

int	handle_output_redirect(char *command, int original_fds[2])
{
	save_original_fd_out(original_fds);
	if (redirect_output(command) == FAILED)
	{
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}
