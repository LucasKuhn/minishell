/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:18 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/01 18:29:11 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*input_redirect_position(char *str)
{
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
		if (*str == '<')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*redirect_file_name(char *redirect_str)
{
	int		name_start;
	int		name_end;
	char	*name;

	name_start = 1;
	while (redirect_str[name_start] == ' ') // TODO: redirect vazio ex: '<'
		name_start++;
	name_end = name_start;
	// TODO: tem que pular as aspas --> grep oi < "arquivo com espaco" ou < "infile"
	while (redirect_str[name_end] && redirect_str[name_end] != ' ')
		name_end++;
	name = ft_substr(redirect_str, name_start, name_end - name_start);
	ft_memmove(redirect_str, &redirect_str[name_end], ft_strlen(&redirect_str[name_end]) + 1);
	return (name);
}

void	handle_input_redirect(char *command)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = input_redirect_position(command);
	if (!input_redirect)
		return ;
	file_name = redirect_file_name(input_redirect);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror("minishell: input fd open error"); // TODO: arrumar a mensagem
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
}
