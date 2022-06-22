/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 22:30:03 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 14:58:12 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the string ’s’ to the given file descriptor 'fd'.
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, sizeof(*s) * ft_strlen(s));
}
