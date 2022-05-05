// // ◦ cd with only a relative or absolute path
// // ◦ pwd with no options
// // ◦ export with no options
// // ◦ unset with no options
// // ◦ env with no options or arguments
// // ◦ exit with no options

#include "minishell.h"

void echo(char **args)
{
	int	i;
	int new_line;

	new_line = 1;
	i = 1;
	if (ft_strncmp(args[i],"-n",3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
}

void cd(char **args)
{
	if (!args[1] || ft_strncmp(args[1],"~",2) == 0)
		chdir(getenv("HOME"));
	else if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putstr_fd(": ",1);
		perror("");
	}
}

void pwd(char **args)
{
	char cwd[100];
	getcwd(cwd, 100);
	ft_putstr_fd(cwd,1);
	ft_putstr_fd("\n", 1);
}

void env(char **args, t_env *envp)
{
	t_env *aux = envp;

	while (aux)
	{
		ft_putstr_fd(aux->str,1);
		ft_putstr_fd("\n",1);
		aux = aux->next;
	}
}

// TODO: Conferir o que o export deve fazer quando não recebe nada
void export(char **args, t_env *envp)
{
	// char *key_pair;
	// char *name;
	// char *value;
	// int i;

	// key_pair = args[1];
	// i = 0;
	// while (key_pair[i] != '=')
	// 	i++;
	// name = ft_substr(key_pair, 0, i);
	// value = ft_substr(key_pair, i+1, ft_strlen(key_pair));
}