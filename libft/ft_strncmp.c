/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:55:42 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/10 19:34:25 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!n)
	{
		return (0);
	}
	i = 0;
	while (*s1 && *s2 && (*s1 == *s2) && (i + 1 < n))
	{
		++s1;
		++s2;
		++i;
	}
	return (((unsigned char)*s1) - ((unsigned char)*s2));
}
