#include "minishell.h"

char *get_prompt()
{
	char *prompt;
	char *user; 
	char *cwd; 
	char *directory;

	getcwd(cwd, 1024);
	user = getenv("USER");
	directory = ft_strrchr(cwd, '/') + 1; 

	ft_strlcat(prompt, GRN, 99);
	ft_strlcat(prompt, user, 99);
	ft_strlcat(prompt, WHT, 99);
	ft_strlcat(prompt, "@", 99);
	ft_strlcat(prompt, MAG, 99);
	ft_strlcat(prompt, directory, 99);
	ft_strlcat(prompt, CRESET, 99);
	return(prompt);
}