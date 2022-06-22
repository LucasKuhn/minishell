/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:42:57 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/22 16:03:10 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	starts_with_pipe(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	redirect_without_label(char *input)
{
	char	*redirect_position;
	char	next_redirect;

	next_redirect = get_next_redirect(input);
	redirect_position = get_redirect_position(input, next_redirect);
	if (!redirect_position)
		return (FALSE);
	if (redirect_position[0] == '<' && redirect_position[1] == '<')
		redirect_position++;
	else if (redirect_position[0] == '>' && redirect_position[1] == '>')
		redirect_position++;
	redirect_position++;
	while (*redirect_position == ' ' || *redirect_position == '\t')
		redirect_position++;
	if (*redirect_position == '\0')
		return (syntax_error("newline"));
	if (is_invalid_token(*redirect_position))
		return (unexpected_token(redirect_position));
	return (redirect_without_label(redirect_position));
}

int	has_empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	return (has_empty_pipe(next_pipe));
}

int	is_invalid_syntax(char *input)
{
	if (starts_with_pipe(input))
		return (TRUE);
	if (redirect_without_label(input))
		return (TRUE);
	if (has_empty_pipe(input))
		return (TRUE);
	return (FALSE);
}
