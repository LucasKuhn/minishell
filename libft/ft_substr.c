/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:54:16 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 15:24:07 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 @brief Allocates (with malloc(3)) and returns a substring from the string ’s’.
 The substring begins at index ’start’ and is of maximum size ’len’.
 @param s The string from which to create the substring.
 @param start The start index of the substring in the string ’s’.
 @param len The maximum length of the substring.
 @return char* The substring. NULL if the allocation fails.
**/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*substring_start;
	size_t	s_size;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (len > s_size)
		len = s_size;
	substring = malloc(sizeof(*s) * len + 1);
	if (!substring)
		return (NULL);
	while (*s && start--)
		s++;
	substring_start = substring;
	while (*s && len)
	{
		*substring = *s;
		substring++;
		s++;
		len--;
	}
	*substring = '\0';
	return (substring_start);
}
