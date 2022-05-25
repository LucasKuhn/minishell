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

# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

# define TRUE 1
# define FALSE 0

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

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;

// minishell
int minishell(t_env	*minienv);

// prompt functions
char *prompt_input(t_env *minienv);

// builtin functions
int		is_builtin(char *command);
int		execute_forked_builtin(char **args, t_env **minienv);
int		execute_builtin(char **args, t_env **minienv);
int		cd(char **args, t_env *minienv);
int		echo(char **args);
int		pwd();
int		export(char **args, t_env **minienv);
int		env(t_env *envp);
int		unset(char **args, t_env **minienv);
int		builtin_exit();

// executes
int execute_one_command(char *command, t_env	**minienv);
int execute_multiple_commands(char **commands, t_env **minienv);

// env functions
t_env	*init_minienv(char **envp);
char	*minienv_value(char *name, t_env *minienv);
t_env	*minienv_node(char *name, t_env *minienv);
void	minienv_update(char *name, char *value, t_env *minienv);
void	list_append(char *key_pair, t_env **list);
char	**minienv_to_envp(t_env *minienv);

// generic execute function
int	execute_command(char **args, t_env *minienv);
int	wait_for_child(int child_pid);

// redirects
void	redirect_fd(int fd_to_redirect, int fd_location);
void	redirect_fds(int fd_in, int fd_out);

// str functions
char	*name_only(char *key_pair);
char	*value_only(char *key_pair);
int		str_equal(const char* str1, const char* str2);
char	*ft_strsjoin(int n, char *str1, ...);
void	strs_cat(char *base, char *str1, char *str2, char *str3);
int		is_quote(char c);
int		is_empty(char *str);

// signals
void	define_main_signals();
void	define_execute_signals();

// tokenizer
char	**split_args(char *command);

// pipes
char	**split_commands(char *input);

// error checker
int		has_unclosed_quotes(char *str);
#endif
