#include "minishell.h"

char *get_prompt_str(t_env *minienv)
{
	char *user;
	char *cwd;
	char *directory;
	static char prompt[PATH_MAX];

	user = minienv_value("USER", minienv);
	cwd = minienv_value("PWD", minienv);
	directory = ft_strrchr(cwd, '/') + 1;
	if (ft_strncmp(cwd, "/", 2) == 0)
		directory = "ROOT";
	ft_bzero(prompt, sizeof(prompt));
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

char *prompt_input(t_env *minienv)
{
	char *input;

	input = readline(get_prompt_str(minienv));
	if (input && *input)
		add_history(input);
	return (input);
}
