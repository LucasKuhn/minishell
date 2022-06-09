/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:13 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/09 17:02:35 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTES_H
# define EXECUTES_H

# define IN 0
# define OUT 1

// executes
int		execute_one_command(char *command, t_env	**minienv);
int		execute_multiple_commands(char **commands, t_env **minienv);

// execute builtin
int		execute_forked_builtin(char **args, t_env **minienv, char **commands);
int		execute_builtin(char **args, t_env **minienv);

// execute external
int		execute_external(char **args, t_env *minienv);
char	*get_path(char *command, t_env *minienv);

// wait after fork
int		wait_for_child(int child_pid, int is_last_child);
int		wait_for_children(int children_pid[1024]);

// redirects
void	redirect_fd(int fd_to_redirect, int fd_location);
void	redirect_fds(int fd_in, int fd_out);
int		redirect_input(char *command);
char	*input_redirect_position(char *str);
void	close_all_fds(void);
void	close_extra_fds(void);
int		has_input_redirect(char *command);

// pipes 
void	handle_pipe(int original_fd_out, char *current_command, char **commands);

#endif
