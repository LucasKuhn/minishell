/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:38:23 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/28 18:51:35 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "minishell.h"

// Wildcard
void		expand_wildcards(char *search, char **input, t_env *minienv);
char		*get_wildcard_value(char *wildcard_label, t_env *minienv);

#endif
