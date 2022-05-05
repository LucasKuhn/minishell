#include "minishell.h"

char *get_prompt()
{
	char *prompt;
	char *user; 
	char *cwd; 
	char *directory;

	user = getenv("USER"); 
	cwd = getenv("PWD"); 
	// directory = ft_strrchr(cwd, '/') + 1; 
	directory = cwd; 

	prompt = malloc(sizeof(char) * PATH_MAX);
	ft_strlcat(prompt, GRN, PATH_MAX);
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, WHT, PATH_MAX);
	ft_strlcat(prompt, "@", PATH_MAX);
	ft_strlcat(prompt, MAG, PATH_MAX);
	ft_strlcat(prompt, directory, PATH_MAX);
	ft_strlcat(prompt, CRESET, PATH_MAX);
	ft_strlcat(prompt, " > ", PATH_MAX);
	return(prompt);
}