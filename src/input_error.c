/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:45:56 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/21 15:49:11 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_input_error(char *input, int *exit_status, t_env *minienv)
{
	if (has_unclosed_quotes(input))
		return (TRUE);
	if (is_invalid_syntax(input))
	{
		*exit_status = 1;
		return (TRUE);
	}
	if (handle_heredoc(input, exit_status, minienv) == FAILED)
		return (TRUE);
	return (FALSE);
}
