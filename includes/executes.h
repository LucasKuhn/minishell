/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:13 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/08 18:32:14 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTES_H
# define EXECUTES_H

// executes
int		execute_one_command(char *command, t_env	**minienv);
int		execute_multiple_commands(char **commands, t_env **minienv);

// execute builtin
int		execute_forked_builtin(char **args, t_env **minienv, char **commands);
int		execute_builtin(char **args, t_env **minienv);

// execute external
int		execute_external(char **args, t_env *minienv);
char	*get_path(char *command, t_env *minienv);
int		wait_for_children(int children_pid[1024]);
int		wait_for_child(int child_pid);

// redirects
void	redirect_fd(int fd_to_redirect, int fd_location);
void	redirect_fds(int fd_in, int fd_out);
void	prepare_io(int fd_stdout, int is_first_command, int has_next_command);
int		redirect_input(char *command);
char	*input_redirect_position(char *str);
void	close_all_fds(void);
void	close_extra_fds(void);

#endif
