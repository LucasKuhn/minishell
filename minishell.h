/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:36:50 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/05 20:20:11 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Prompt colors
# define GRN	"\001\e[0;32m\002"
# define MAG	"\001\e[0;35m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define PATH_MAX	4096

# define INTERRUPT	128
# define CMD_NOT_FOUND	127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2

# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

# define TRUE 1
# define FALSE 0

# define REDIRECT_FAILURE -1

#define LLONG_MAX 9223372036854775807

# include "42-libraries/libft/libft.h" // libft
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getwd ttyname
# include <stdio.h> // perror
# include <stdarg.h> // va_arg
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;

// minishell
int		minishell(t_env	*minienv);

// prompt functions
char	*prompt_input(t_env *minienv);

// builtin functions
int		is_builtin(char *command);
int		execute_forked_builtin(char **args, t_env **minienv, char **commands);
int		execute_builtin(char **args, t_env **minienv);
int		cd(char **args, t_env *minienv);
int		echo(char **args);
int		pwd(void);
int		export(char **args, t_env **minienv);
int		env(t_env *envp);
int		unset(char **args, t_env **minienv);
int		builtin_exit(char **args, t_env **minienv);

// executes
int		execute_one_command(char *command, t_env	**minienv);
int		execute_multiple_commands(char **commands, t_env **minienv);

// env functions
t_env	*init_minienv(char **envp);
char	*minienv_value(char *name, t_env *minienv);
t_env	*minienv_node(char *name, t_env *minienv);
void	minienv_update(char *name, char *value, t_env *minienv);
void	list_append(char *key_pair, t_env **list);
char	**minienv_to_envp(t_env *minienv);
void	free_minienv(t_env **minienv);

// generic execute function
int		execute_command(char **args, t_env *minienv);
int		wait_for_child(int child_pid);

// redirects
void	redirect_fd(int fd_to_redirect, int fd_location);
void	redirect_fds(int fd_in, int fd_out);
void	prepare_io(int fd_stdout, int is_first_command,
		int has_next_command);
int		handle_input_redirect(char *command);
char	*input_redirect_position(char *str);

// str functions
char	*name_only(char *key_pair);
char	*value_only(char *key_pair);
int		str_equal(const char *str1, const char *str2);
char	*ft_strsjoin(int n, char *str1, ...);
void	strs_cat(char *base, char *str1, char *str2, char *str3);
int		is_quote(char c);
int		is_empty(char *str);
void	free_array(char **arr);

// signals
void	define_main_signals(void);
void	define_execute_signals(int child_pid);

// tokenizer
char	**split_args(char *command);

// pipes
char	**split_commands(char *input);

// error checker
int		has_unclosed_quotes(char *str);

// utils
void		expand_variables(char **commands, t_env *minienv, int exit_status);
void		exit_with_error(char *command, char *msg, int error);
void		print_error_msg(char *command, char *msg);
void		print_perror_msg(char *command, char *perror_msg);
void		close_all_fds();
void		close_extra_fds();
long long	ft_atoll(const char *str);

// builtin utils
int is_varname(char c);

#endif
