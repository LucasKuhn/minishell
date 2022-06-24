/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:13 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/23 18:20:00 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTES_H
# define EXECUTES_H

# define IN 0
# define OUT 1

// executes
int		execute_one_command(char *command, t_env	**minienv);
int		execute_multiple_commands(char **commands, t_env **minienv);

// one command utils
void	save_original_fd_in(int original_fds[2]);
void	save_original_fd_out(int original_fds[2]);
int		handle_input_redirect(char *command, int original_fds[2]);
int		handle_output_redirect(char *command, int original_fds[2]);

// multiple commands utils
int		*init_children_pid(char **commands);
void	clean_after_execute(int *children_pid);
void	quit_child(char **commands, t_env **minienv);

// execute builtin
int		execute_forked_builtin(char **args, t_env **minienv);
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
int		redirect_output(char *command);
char	*get_redirect_position(char *str, char redirect_char);
char	get_next_redirect(char *str);
void	close_all_fds(void);
void	close_extra_fds(void);
char	*get_label_name(char *redirect_str);
void	redirect_heredoc(char *command, int heredoc_number);

// pipes
void	handle_pipe(int original_out, char *current_command, char **commands);

#endif
