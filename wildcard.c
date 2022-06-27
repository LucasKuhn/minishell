#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;
	size_t	size;

	size = ft_strlen(s) + 1;
	copy = (char *)malloc(size * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;
	size_t			buffer;

	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) < len)
		buffer = ft_strlen((char *)s);
	else
		buffer = len;
	substring = (char *)malloc((buffer + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && ((start + i) < ft_strlen((char *)s)))
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}

char	*get_wildcard_label_position(char *str)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '*')
		{
			while (*str != ' ' && str > start) // verificar que provavelmente não é só espaço
				str--;
			if (*str == ' ')
				str++;
			return (str);
		}
		str++;
	}
	return (NULL);
}

void	update_input(char **input, char *wildcard_value, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	if (!*input[0] && !wildcard_value)
		first_part = ft_strdup("");
	else if (!*input[0] && wildcard_value)
		first_part = ft_strdup(wildcard_value);
	else if (!wildcard_value)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, wildcard_value);
	updated_input = ft_strjoin(first_part, second_part);
	free(first_part);
	free(*input);
	*input = updated_input;
}

void	remove_new_lines(char *wildcard_value)
{
	while (*wildcard_value)
	{
		if (*wildcard_value == '\n' && wildcard_value[1])
			*wildcard_value = ' ';
		else if (*wildcard_value == '\n')
			*wildcard_value = '\0';
		wildcard_value++;
	}
}

char	**get_args(char *wildcard_label)
{
	char	**args;

	args = malloc(sizeof(char *) * 11);
	args[0] = "find";
	args[1] = ".";
	args[2] = "-maxdepth";
	args[3] = "1";
	args[4] = "-name";
	args[5] = wildcard_label;
	args[6] = "-exec";
	args[7] = "basename";
	args[8] = "{}";
	args[9] = ";";
	args[10] = NULL;
	return (args);
}

void	expand_wildcards(char **input, char *envp[])
{
	char	*wildcard_label_position;
	static char	wildcard_value[4096];
	int		child_pid;
	int		pipe_fds[2];
	char	*second_part;
	char	*wildcard_label;
	int		label_size;

	//echo 'bye *' t*.c bye
	wildcard_label_position = get_wildcard_label_position(*input);
	if (!wildcard_label_position)
		return ;
	label_size = 0;
	while (wildcard_label_position[label_size + 1] && wildcard_label_position[label_size + 1] != ' ')
		label_size++;
	wildcard_label = ft_substr(wildcard_label_position, 0, label_size + 1);
	*wildcard_label_position = '\0';
	second_part = &wildcard_label_position[label_size + 1];
	printf("first_part = |%s|\n", *input);
	printf("wildcard_label = |%s|\n", wildcard_label);
	printf("second_part = |%s|\n", second_part);
	pipe(pipe_fds);
	child_pid = fork();
	/* if (child_pid == -1)
		printf("fork", "wildcard"); */
	if (child_pid == 0)
	{
		/* rl_clear_history();
		envp = minienv_to_envp(minienv);
		free_minienv(&minienv); */
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
		if (execve("/usr/bin/find", get_args(wildcard_label), envp) == -1)
		{
			printf("deu pau\n");
			exit(1);
		}
	}
	else
	{
		close(pipe_fds[1]);
		waitpid(child_pid, NULL, 0);
		read(pipe_fds[0], wildcard_value, 200);
		remove_new_lines(wildcard_value);
		printf("filho terminou\n");
		printf("wildcard_value = |%s|\n", wildcard_value);
		printf("before update = |%s|\n", *input);
		update_input(input, wildcard_value, second_part);
		printf("after update = |%s|\n", *input);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	if (argc > 1)
	{
		input = ft_strdup(argv[1]);
		expand_wildcards(&input, envp);
		free(input);
	}
	return (0);
}

// *.c X
// test*.c
// echo test*.c
// echo 'bye *' test*.c bye
// echo 'bye *' mini* bye
// echo *
// echo "*"
// "*"
// test*
// *
// <*.txt
