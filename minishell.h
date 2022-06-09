/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:36:50 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 14:37:14 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Prompt colors
# define GRN	"\001\e[0;32m\002"
# define MAG	"\001\e[0;35m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807

# define NO_REDIRECT -1
# define REDIRECT_FAILURE -1

# include "allowed_libs.h"
# include "errors.h"
# include "minienv.h"
# include "builtins.h"
# include "executes.h"

// minishell
int			minishell(t_env	*minienv);

// prompt
char		*prompt_input(t_env *minienv);

// syntax
int			has_unclosed_quotes(char *str);

// tratativas
void		handle_expansions(char **input, t_env *minienv, int exit_status);
void		expand_variables(char **input, t_env *minienv);
void		expand_exit_status(char **input, int exit_status);

// command table
char		**split_commands(char *input);

// tokenizer
char		**split_args(char *command);

// signals
void		define_main_signals(void);
void		define_execute_signals(int child_pid);

// utils
int			str_equal(const char *str1, const char *str2);
int			is_quote(char c);
int			is_empty(char *str);
int			contains_pipe(char *str);
void		free_array(char **arr);
long long	ft_atoll(const char *str);

#endif
