/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allowed_libs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:54:09 by sguilher          #+#    #+#             */
/*   Updated: 2022/06/22 15:46:09 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOWED_LIBS_H
# define ALLOWED_LIBS_H

# include "libft/libft.h" // libft
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getwd ttyname
# include <stdio.h> // perror
# include <stdarg.h> // va_arg
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

#endif
