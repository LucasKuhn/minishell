/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:01:45 by lalexk-ku         #+#    #+#             */
/*   Updated: 2022/06/24 18:57:02 by lalex-ku         ###   ########.fr       */
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
