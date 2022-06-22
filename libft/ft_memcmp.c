/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 19:51:40 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 14:48:42 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two string and returns the difference between
 * the first different char
 * @details How much bigger s1 is than s2
 * @param s1
 * @param s2
 * @param n Amount of chars to compare
 * @return int -> 1 if s1 is bigger, -1 if s2 is bigger, 0 if they are the same
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_chars;
	const unsigned char	*s2_chars;

	s1_chars = s1;
	s2_chars = s2;
	while (n)
	{
		if (*s1_chars != *s2_chars)
			return ((unsigned char)*s1_chars - (unsigned char)*s2_chars);
		s1_chars++;
		s2_chars++;
		n--;
	}
	return (0);
}
