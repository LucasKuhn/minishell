/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:19:08 by coder             #+#    #+#             */
/*   Updated: 2022/06/24 19:34:28 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_varname(char *name)
{
	if (!ft_isalpha(*name))
		return (FALSE);
	while (*name)
	{
		if (!is_varname(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}
