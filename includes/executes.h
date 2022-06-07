/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:41:13 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/06/07 15:41:42 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTES_H
# define EXECUTES_H

// executes
int			execute_one_command(char *command, t_env	**minienv);
int			execute_multiple_commands(char **commands, t_env **minienv);

// generic execute function
int			execute_command(char **args, t_env *minienv);
int			wait_for_child(int child_pid);

// redirects
void		redirect_fd(int fd_to_redirect, int fd_location);
void		redirect_fds(int fd_in, int fd_out);
void		prepare_io(int fd_stdout, int is_first_command,
				int has_next_command);
int			handle_input_redirect(char *command);
char		*input_redirect_position(char *str);
void		close_all_fds(void);
void		close_extra_fds(void);

#endif
