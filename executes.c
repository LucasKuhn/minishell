#include "minishell.h"

static void prepare_io(int fd_stdout, int is_first_command, int has_next_command)
{
	int fd_in; 
	int fd_out; 
	static int fds_pipe[2];

	fd_in = STDIN_FILENO;
	if (!is_first_command)
		fd_in = fds_pipe[0];
	if (has_next_command)
	{
		if (pipe(fds_pipe) == -1)
			perror("minishell : ");
		fd_out = fds_pipe[1];
	}
	else
		fd_out = fd_stdout;
	redirect_fds(fd_in, fd_out);
}

int execute_one_command(char *command, t_env **minienv)
{
	char **args;
	
	args = split_args(command);
	if (is_builtin(args[0]))
		return(execute_builtin(args, minienv));
	else
		return(execute_command(args, *minienv));
}

int execute_multiple_commands(char **commands, t_env **minienv)
{
	char	**args;
	int		original_fds[2];
	int		exit_status;
	int		is_first_command;

	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	is_first_command = TRUE;
	while (*commands)
	{
		args = split_args(*commands); //TODO: limpar args
		prepare_io(original_fds[1], is_first_command, (commands[1] != NULL));
		if (is_builtin(args[0]))
			exit_status = execute_forked_builtin(args, minienv);
		else
			exit_status = execute_command(args, *minienv);
		is_first_command = FALSE;
		commands++;
	}
	redirect_fd(original_fds[0], STDIN_FILENO);
	return(exit_status);	
}