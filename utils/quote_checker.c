/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:13:19 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/25 16:12:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(void)
{
	ft_putstr_fd("Tem aspa aberta aí queridão 🌝\n", STDERR_FILENO);
	return (1);
}

int	has_unclosed_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
			last_opened = *str;
		str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
			last_opened = 0;
		str++;
	}
	if (*str)
		return (has_unclosed_quotes(str));
	else
	{
		if (!last_opened)
			return (0);
		else
			return (print_error()); // TODO: Talvez dá pra tirar esse else
	}
	return (print_error());
}
