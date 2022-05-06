#include "minishell.h"

char *get_prompt(t_env *minienv)
{
	char *prompt;
	char *user;
	char *cwd;
	char *directory;

	user = var_value(get_minienv("USER", minienv)->key_pair);
	cwd = var_value(get_minienv("PWD", minienv)->key_pair);
	// directory = ft_strrchr(cwd, '/') + 1;
	directory = cwd;
	// TODO: acho que não precisa alocar
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
