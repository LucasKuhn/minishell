// // ◦ echo with option -n
// // ◦ cd with only a relative or absolute path
// // ◦ pwd with no options
// // ◦ export with no options
// // ◦ unset with no options
// // ◦ env with no options or arguments
// // ◦ exit with no options

// #include "minishell.h"

// void echo(str)
// {
// 	write(1, str, ft_strlen(str));
// }

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
// 	// TODO
// }