// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

#include "minishell.h"

void cd(char *str)
{
	if (chdir(str) != 0)
		perror("cd");
}

void echo(str)
{
	write(STDOUT, str, ft_strlen(str));
}

void pwd()
{
	char *cwd;
	cwd = getenv("PWD"); 
	echo(cwd);
}

void export()
{
	// TODO
}