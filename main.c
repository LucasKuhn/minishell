/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:51:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/13 18:56:43 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input;
	char	**args;
	char	**commands;
	char	*command_name;
	t_env	*minienv;
	int		has_pipe;
	int		fds_pipe[2];
	int		fd_stdin;
	int		fd_stdout;
	int		fd_in;
	int		fd_out;
	int		has_next_command;

	(void) argc;
	(void) argv;
	exit_status = 0;
	minienv = init_minienv(envp);
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (!input)
			builtin_exit(args, &minienv);
		if (!*input)
			continue;
		if (has_unclosed_quotes(input))
			continue;
		commands = split_commands(input);
		has_pipe = (commands[1] != NULL);
		fd_stdin = dup(STDIN_FILENO);
		fd_stdout = dup(STDOUT_FILENO);
		fd_in = STDIN_FILENO;
		fd_out = STDOUT_FILENO;
		while (*commands)
		{
			args = split_args(*commands);
			command_name = args[0];
			has_next_command = commands[1] != NULL;
			if (has_next_command)
			{
				if (pipe(fds_pipe) == -1)
					perror("minishell : ");
				fd_out = fds_pipe[1];
			}
			else
				fd_out = fd_stdout;
			redirect_fds(fd_in, fd_out);
			if (is_builtin(command_name))
				exit_status = execute_builtin(args, &minienv, has_pipe);
			else
				exit_status = execute_command(args, minienv);
			if (has_next_command)
				fd_in = fds_pipe[0];
			commands++;
			//TODO: limpar args
		}
		dup2(fd_stdin, STDIN_FILENO);
		//TODO: limpar commands
	}
	// TODO: como lidar para limpar quando acionar a exit (Ctrl+D)
	return (exit_status);
}
