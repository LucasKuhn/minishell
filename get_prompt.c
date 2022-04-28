#include "minishell.h"

char *get_prompt()
{
	char *prompt;
	char *user; 
	char *cwd; 
	char *directory;

	user = getenv("USER"); 
	cwd = getenv("PWD"); 
	directory = ft_strrchr(cwd, '/') + 1; 

	prompt = malloc(sizeof(char) * 256);
	ft_strlcat(prompt, GRN, 99);
	ft_strlcat(prompt, user, 99);
	ft_strlcat(prompt, WHT, 99);
	ft_strlcat(prompt, "@", 99);
	ft_strlcat(prompt, MAG, 99);
	ft_strlcat(prompt, directory, 99);
	ft_strlcat(prompt, CRESET, 99);
	ft_strlcat(prompt, " > ", 99);
	return(prompt);
}