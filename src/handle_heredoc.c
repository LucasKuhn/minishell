/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:46:10 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/28 18:51:00 by lalex-ku         ###   ########.fr       */
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

void	read_heredoc(int *exit_status, t_env *minienv, char *delimiter,
		int heredoc_number)
{
	char	*line_read;
	char	*filename;
	int		tmp_file_fd;

	filename = tmp_filename(heredoc_number);
	tmp_file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	line_read = readline("> ");
	while (line_read && !str_equal(line_read, delimiter))
	{
		expand_exit_status(&line_read, *exit_status);
		expand_variables(&line_read, minienv);
		ft_putstr_fd(line_read, tmp_file_fd);
		ft_putchar_fd('\n', tmp_file_fd);
		free(line_read);
		line_read = readline("> ");
	}
	if (!line_read)
		print_error_msg("warning: heredoc delimited by EOF. Wanted", delimiter);
	free(line_read);
	close(tmp_file_fd);
	free(delimiter);
	free_minienv(&minienv);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	exec_heredoc(char *delimiter, int heredoc_number, int *exit_status,
		t_env *minienv)
{
	int	child_pid;

	child_pid = fork();
	define_heredoc_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - heredoc_prompt", delimiter);
	else if (child_pid == 0)
		read_heredoc(exit_status, minienv, delimiter, heredoc_number);
	else
	{
		*exit_status = wait_for_child(child_pid, TRUE);
		define_main_signals();
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}

int	handle_heredoc(char *input, int *exit_status, t_env *minienv)
{
	static int	heredoc_number;
	char		*heredoc_position;
	char		*delimiter;

	heredoc_number = -1;
	heredoc_position = get_heredoc_position(input);
	if (!heredoc_position)
		return (SUCCESS);
	heredoc_number--;
	*heredoc_position = heredoc_number;
	heredoc_position++;
	delimiter = get_label_name(heredoc_position);
	if (!exec_heredoc(delimiter, heredoc_number, exit_status, minienv))
	{
		free(delimiter);
		return (FAILED);
	}
	free(delimiter);
	return (handle_heredoc(input, exit_status, minienv));
}
