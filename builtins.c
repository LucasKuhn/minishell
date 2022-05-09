// // ◦ cd with only a relative or absolute path
// // ◦ pwd with no options
// // ◦ export with no options
// // ◦ unset with no options
// // ◦ env with no options or arguments
// // ◦ exit with no options

#include "minishell.h"

void echo(char **args)
{
	int i;
	int new_line;

	new_line = 1;
	i = 1;
	if (ft_strncmp(args[i], "-n", 3) == 0)
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

void cd(char **args, t_env *minienv)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = minienv_value("HOME", minienv);
	if (chdir(path) == 0)
	{
		minienv_update("OLDPWD", minienv_value("PWD", minienv), minienv);
		getcwd(cwd, PATH_MAX);
		minienv_update("PWD", cwd, minienv);
	}
	else
	{
		// Good place where we may way want to use printf("%s")
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putstr_fd(": ", 1);
		perror("");
	}
}

void pwd(char **args)
{
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
}

void env(char **args, t_env *minienv)
{
	t_env *aux;

	aux = minienv;
	while (aux)
	{
		ft_putstr_fd(aux->key_pair, 1);
		ft_putstr_fd("\n", 1);
		aux = aux->next;
	}
}

void declare_env(char **args, t_env *minienv)
{
	t_env *aux;

	aux = minienv;
	while (aux)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(aux->key_pair, 1);
		ft_putstr_fd("\n", 1);
		aux = aux->next;
	}
}
// TODO: Conferir o que o export deve fazer quando não recebe nada
void export(char **args, t_env **minienv)
{
	char *key_pair;
	char *name;
	int	size;
	t_env	*aux;

	key_pair = args[1];
	if (!key_pair)
		return(declare_env(args, *minienv));
	name = name_only(key_pair);
	if (name == NULL)
		return ;
	aux = *minienv;
	size = ft_strlen(name) + 1;
	while (aux)
	{
		if (ft_strncmp(aux->key_pair, key_pair, size) == 0)
		{
			free(aux->key_pair);
			aux->key_pair = ft_strdup(key_pair);
			return ;
		}
		aux = aux->next;
	}
	list_append(key_pair, minienv);
}

void unset(char **args, t_env **minienv)
{
	char *name;
	t_env *aux;
	t_env *temp;

	name = args[1];
	if (!name)
		return ;
	if (ft_strrchr(name, '=') != 0)
		return(ft_putstr_fd("invalid parameter name\n", 2)); // TODO: Aqui da pra usar o printffd
	aux = *minienv;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->key_pair, name, ft_strlen(name)) == 0)
		{
			if ((aux->next)->key_pair[ft_strlen(name)] == '=')
			{
				temp = aux->next;
				aux->next = (aux->next)->next;
				free((temp)->key_pair);
				free((temp));
				return;
			}
		}
		aux = aux->next;
	}
}

