#ifndef MINISHELL_H
# define MINISHELL_H

# define GRN "\e[0;32m"
# define MAG "\e[0;35m"
# define WHT "\e[0;37m"
# define CRESET "\e[0m"

# include "libft/libft.h" // libft
#include <readline/readline.h> // readline 
#include <stdlib.h> // getenv
#include <unistd.h> // getwd ttyname

char *get_prompt();

#endif
