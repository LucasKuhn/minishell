/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:17:08 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/22 17:34:16 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIENV_H
# define MINIENV_H

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;

t_env		*init_minienv(char **envp);
t_env		*minienv_node(char *name, t_env *minienv);
char		*minienv_value(char *name, t_env *minienv);
void		minienv_update(char *name, char *value, t_env *minienv);
void		list_append(char *key_pair, t_env **list);
char		**minienv_to_envp(t_env *minienv);
void		free_minienv(t_env **minienv);
char		*create_keypair(char *name, char *value);
char		*name_only(char *key_pair);
char		*value_only(char *key_pair);

#endif
