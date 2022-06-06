/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:19:08 by coder             #+#    #+#             */
/*   Updated: 2022/06/06 21:23:14 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_varname(char *name)
{
	while (*name)
	{
		if (!is_varname(*name))
			return (0);
		name++;
	}
	return (1);
}
