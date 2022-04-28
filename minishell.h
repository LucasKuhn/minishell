#ifndef MINISHELL_H
# define MINISHELL_H

# define GRN "\001\e[0;32m\002"
# define MAG "\001\e[0;35m\002"
# define WHT "\001\e[0;37m\002"
# define CRESET "\001\e[0m\002"

# include "libft/libft.h" // libft
#include <readline/readline.h> // readline 
#include <stdlib.h> // getenv
#include <unistd.h> // getwd ttyname

char *get_prompt();

#endif
