/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:46:10 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/14 19:23:03 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_position(char *str)
{
	while (*str && str[1])
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
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*tmp_filename(int heredoc_number)
{
	char	filename[30];
	char	*number_str;

	ft_bzero(filename, 30);
	number_str = ft_itoa(heredoc_number);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, number_str, 30);
	free(number_str);
	return (ft_strdup(filename));
}

static int	get_heredoc_name_end(char *name)
{
	int	name_end;

	name_end = 0;
	while (name[name_end] && !is_name_delimeter(name[name_end]))
	{
		if (name[name_end] == '\'')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '\'')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] == '"')
		{
			move_one_forward(&name[name_end]);
			while (name[name_end] && name[name_end] != '"')
				name_end++;
			move_one_forward(&name[name_end]);
		}
		else if (name[name_end] && !is_name_delimeter(name[name_end]))
			name_end++;
	}
	return (name_end);
}

char	*get_heredoc_name(char *input, int heredoc_number)
{
	int		name_start;
	int		name_end;
	char	*name;
	char	*remaining_cmd;

	*input = heredoc_number;
	input++;
	move_one_forward(input);
	name_start = 0;
	while (input[name_start] == ' ' || input[name_start] == '\t')
		name_start++;
	name_end = get_heredoc_name_end(&input[name_start]);
	name = ft_substr(&input[name_start], 0, name_end);
	remaining_cmd = &input[name_end];
	ft_memmove(input, remaining_cmd, ft_strlen(remaining_cmd) + 2);
	return (name);
}

void	define_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

int	handle_heredoc(char *input, int *exit_status)
{
	char	*heredoc_position;
	char	*delimiter;
	char	*line_read;
	char	*filename;
	int		tmp_file_fd;
	static int	heredoc_number;
	int		child_pid;

	heredoc_position = get_heredoc_position(input);
	if (!heredoc_position)
		return (SUCCESS);
	if (!heredoc_number)
		heredoc_number = -1;
	heredoc_number--;
	delimiter = get_heredoc_name(heredoc_position, heredoc_number);
	filename = tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	child_pid = fork();
	define_heredoc_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - heredoc_prompt", delimiter);
	else if (child_pid == 0)
	{
		line_read = readline("> ");
		while (line_read && !str_equal(line_read, delimiter))
		{
			ft_putstr_fd(line_read, tmp_file_fd);
			ft_putchar_fd('\n', tmp_file_fd);
			free(line_read);
			line_read = readline("> ");
		}
		if (!line_read)
			print_error_msg("warning: here-document delimited by end-of-file. Wanted", delimiter);
		free(line_read);
		close(tmp_file_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(tmp_file_fd);
		*exit_status = wait_for_child(child_pid, TRUE);
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	define_main_signals();
	return (handle_heredoc(input, exit_status));
}
