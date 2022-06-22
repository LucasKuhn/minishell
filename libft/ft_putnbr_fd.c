/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:04:01 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 18:57:18 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int n, int power);
static int	ft_digits_in_number(int n);

// Outputs the integer ’n’ to the given file descriptor 'fd'.
void	ft_putnbr_fd(int n, int fd)
{
	long int	number;
	int			power;
	char		c;

	number = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		number = -number;
	}
	power = ft_digits_in_number(number);
	while (number >= 0 && power--)
	{
		c = '0' + (number / ft_power(10, power));
		ft_putchar_fd(c, fd);
		number = number % ft_power(10, power);
	}
	return ;
}

static int	ft_power(int n, int power)
{
	if (power == 0)
		return (1);
	return (n * ft_power(n, power - 1));
}

static int	ft_digits_in_number(int n)
{
	if (n / 10 == 0)
		return (1);
	return (1 + ft_digits_in_number(n / 10));
}
