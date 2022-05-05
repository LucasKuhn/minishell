// // ◦ echo with option -n
// // ◦ cd with only a relative or absolute path
// // ◦ pwd with no options
// // ◦ export with no options
// // ◦ unset with no options
// // ◦ env with no options or arguments
// // ◦ exit with no options

#include "minishell.h"

void echo(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
	{
		ft_putstr_fd(strs[i], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
}

// void cd(char *str)
// {
// 	if (chdir(str) != 0)
// 		perror("cd");
// }

// void pwd()
// {
// 	char *cwd;
// 	cwd = getenv("PWD");
// 	echo(cwd);
// }

// void export()
// {
// 	TODO
// }
