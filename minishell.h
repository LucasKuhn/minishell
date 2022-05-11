#ifndef MINISHELL_H
# define MINISHELL_H

// Prompt colors
# define GRN	"\001\e[0;32m\002"
# define MAG	"\001\e[0;35m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define PATH_MAX	4096

# define INTERRUPT	128

# include "42-libraries/libft/libft.h" // libft
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getwd ttyname
# include <stdio.h> // perror
# include <stdarg.h> // va_arg
# include <sys/wait.h> // waitpid
# include <signal.h> // sigaction

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;

// prompt functions
char *prompt_input(t_env *minienv);

// builtin functions
void	cd(char **args, t_env *minienv);
void	echo(char **strs);
void	pwd(char **args);
void	export(char **args, t_env **minienv);
void	env(char **args, t_env *envp);
void	unset(char **args, t_env **minienv);
void	builtin_exit();

// env functions
t_env	*init_minienv(char **envp);
char	*minienv_value(char *name, t_env *minienv);
t_env	*minienv_node(char *name, t_env *minienv);
void	minienv_update(char *name, char *value, t_env *minienv);
void	list_append(char *key_pair, t_env **list);
char	**minienv_to_envp(t_env *minienv);

// generic execute function
int	execute_command(char **args, t_env *minienv);

// str functions
char	*name_only(char *key_pair);
char	*value_only(char *key_pair);
int		str_equal(const char* str1, const char* str2);
char	*ft_strsjoin(int n, char *str1, ...);
void	strs_cat(char *base, char *str1, char *str2, char *str3);
int		is_quote(char c);

// signals
void	define_main_signals();
void	define_execute_signals();

// tokenizer
char	**split_args(char *command);

#endif
