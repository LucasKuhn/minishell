/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:38:23 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/29 17:01:30 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "minishell.h"

// Wildcard
void	expand_wildcards(char *search, char **input, t_env *minienv);
char	*get_wildcard_value(char *wildcard_label, char **input, t_env *minienv);

#endif
