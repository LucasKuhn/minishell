/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:51:24 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/28 18:42:43 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	handle_expansions(char **input, t_env *minienv, int exit_status)
{
	expand_exit_status(input, exit_status);
	expand_variables(input, minienv);
	expand_wildcards(input[0], input, minienv);
}
