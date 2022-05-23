/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:44:34 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/05/23 15:13:14 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int simple_execute(char *command, t_env	**minienv)
// {
// 	char **args;
	
// 	args = split_args(*command);
// 	if (is_builtin(args[0]))
// 		return(execute_builtin(args, minienv));
// 	else
// 		return(execute_command(args, *minienv));
// }

int minishell(t_env	*minienv)
{
	int		exit_status;
	char	*input;
	char	**args;
	char	**commands;
	char	*command_name;
	int		has_pipe;
	int		fds_pipe[2];
	int		fd_stdin;
	int		fd_stdout;
	int		fd_in;
	int		fd_out;
	int		has_next_command;

	exit_status = 0;
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
				exit_status = execute_forked_builtin(args, &minienv, has_pipe);
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