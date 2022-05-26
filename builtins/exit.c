/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:02:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/26 11:17:44 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_env **minienv)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	free_minienv(minienv);
	exit(EXIT_SUCCESS);
}
