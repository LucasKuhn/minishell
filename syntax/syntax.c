/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:42:57 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/21 16:10:34 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return(syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return(syntax_error(">>"));
	input[1] = '\0';
	return(syntax_error(input));
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
		return(syntax_error("newline"));
	if (is_invalid_token(*redirect_position))
		return(unexpected_token(redirect_position));
	return (redirect_without_label(redirect_position));
}

int	starts_with_pipe(char *input)
{
	if (input[0] == '|')
		return(syntax_error("|"));
	return (FALSE);
}

int	is_invalid_syntax(char *input)
{
	if (starts_with_pipe(input))
		return (TRUE);
	// algo + | + nada --> bash espera input... será que precisamos? "Implement pipes" -> não seria erro de sintaxe
	if (redirect_without_label(input))
		return (TRUE);
	return (FALSE);
}
