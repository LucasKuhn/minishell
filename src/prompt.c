/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:29:21 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/23 14:31:53 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_str(t_env *minienv)
{
	char		*user;
	char		*cwd;
	char		*directory;
	static char	prompt[PATH_MAX];

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
	ft_strlcat(prompt, " 👉 ", PATH_MAX);
	return (prompt);
}

char	*prompt_input(t_env *minienv)
{
	char	*input;

	input = readline(get_prompt_str(minienv));
	if (!input)
		builtin_exit(NULL, &minienv);
	if (input && *input)
		add_history(input);
	return (input);
}
