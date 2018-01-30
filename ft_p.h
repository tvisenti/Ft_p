/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:52:59 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 17:10:07 by tvisenti         ###   ########.fr       */
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
# include <limits.h>
# include "libft/inc/libft.h"

/*
** cmd_get_server
*/

void	cmd_get_server(int fd, char *buf);

/*
** cmd_put_server
*/

void	cmd_put_server(int fd, char *buf);

/*
** cmd_get
*/

void	cmd_get_client(int fd, char *buf);

/*
** cmd_put
*/

void	cmd_put_client(int fd, char *buf);

/*
** handle_file
*/

int		open_file(char *cmd, int fd);
int		open_file_read(char *cmd, int fd);
int		get_size_file(int fd);
int		recv_alert(char *str, int fd);

/*
** display
*/

void	usage(char *str);
int		print_fd_err_int(char *str, int fd);
void	print_fd_err(char *str, int fd);
void	print_fd(char *str, int fd);
int		print_error(char *str);
void	print_error_get_put(char *str);

/*
** server
*/

int		get_cmd(char *str, int fd, char *pwd);
int		create_server(int port);
void	handler_serv(int fd);
int		accept_fork(int sock);

/*
** cmd_server
*/

int		check_permissions(int fd, char *absolute_path);
void	cmd_ls(int fd, char *arg);
void	cmd_cd(int fd, char *arg, char *absolute_path);
void	cmd_pwd(int fd);
void	cmd_mkdir(int fd, char *arg);

/*
** client
*/

void	usage(char *str);
int		create_client(char *addr, int port);
void	wait_user_input(int fd);
void	read_client(int fd, char *buf);

#endif
