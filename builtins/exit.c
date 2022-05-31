/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:02:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/31 14:56:19 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: O exit pode receber um argumento 
// exit takes only integer args in the range 0 - 255
int	builtin_exit(t_env **minienv)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	free_minienv(minienv);
	exit(EXIT_SUCCESS);
}
