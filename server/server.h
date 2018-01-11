/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:31:59 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/11 16:24:18 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/inc/libft.h"
# include <limits.h>

/*
** server
*/

void    usage(char *str);
void	print_fd_err(char *str, int fd);
void	print_fd(char *str, int fd);
int     print_error(char *str);
int     create_server(int port);
void    handler_serv(int fd);
int     accept_fork(unsigned int sock);

/*
** cmd_server
*/

void	cmd_ls(int fd, char *arg);
void	cmd_cd(int fd, char *arg, char *absolute_path);
void	cmd_pwd(int fd);
void	cmd_mkdir(int fd, char *arg);

#endif
