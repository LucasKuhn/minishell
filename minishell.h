#ifndef MINISHELL_H
# define MINISHELL_H

// Prompt colors
# define GRN	"\001\e[0;32m\002"
# define MAG	"\001\e[0;35m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define PATH_MAX	1024

# include "libft/libft.h" // libft
# include <readline/readline.h> // readline
#include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getwd ttyname
# include <stdio.h> // perror

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;

char	*get_prompt();

// builtins functions
void	cd(char **args);
void	echo(char **strs);
void	pwd(char **args);
void	export(char **args, t_env **minienv);
void	env(char **args, t_env *envp);

// env functions
t_env	*get_env(char **envp);
char	*var_name(char *key_pair);
char	*var_value(char *key_pair);
void	var_update(char *key_pair, t_env **minienv);
void	list_append(char *key_pair, t_env **list);

#endif
