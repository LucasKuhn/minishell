/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:12:32 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/15 19:06:25 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies up to (dstsize - 1) characters from the string src to dst,
// NUL-terminating the result if dstsize is not 0
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
	{
		src_size++;
	}
	if (size == 0)
	{
		return (src_size);
	}
	i = 0;
	while ((i < size - 1) && (i < src_size))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_size);
}
