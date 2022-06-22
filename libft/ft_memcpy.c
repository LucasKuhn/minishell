/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:41:43 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 20:23:01 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies 'n' chars from 'src' to 'dst'
// May overlap if the string is the same and 'src' is before 'dst'
// It will copy 'n' characters - see 'strlcpy' for a copy up to NULL
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
		n--;
	}
	return (dst);
}
