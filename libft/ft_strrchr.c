/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:01:45 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/31 20:19:43 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// The strchr() function locates the first occur-
// rence of c (converted to a char) in the string
// pointed to by s.
// Return a pointer to the located character, or NULL if the
// character does not appear in the string
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*location;

	i = 0;
	location = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			location = ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (location);
}
