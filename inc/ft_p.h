/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:52:59 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/12 11:28:27 by tvisenti         ###   ########.fr       */
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
# include "../libft/inc/libft.h"

/*
** BONUS
** Prompt for client
** Cmd: mkdir, lmkdir
** lcd, lls, lpwd
** Everithing is transcripted for server
*/

/*
** handle_file
*/

int		open_file_rdonly(char *cmd, int client);
int		open_file_wronly(char *cmd, int fd);
int		size_file(int fd);
int		recv_alert(char *str, int fd);

/*
** display
*/

void	print_error_get_put(char *str, int file);
void	print_fd_err(char *str, int fd);
void	print_fd(char *str, int fd);
int		print_error(char *str);

/*
** cmd_get_server
*/

void	cmd_get_server(int fd, char *buf);

/*
** cmd_put_server
*/

void	cmd_put_server(int fd, char *buf);

/*
** cmd_server
*/

int		check_permissions_server(int fd, char *absolute_path, char *cur_path);
void	cmd_ls(int fd, char *arg);
void	cmd_cd(int fd, char *arg, char *absolute_path);
void	cmd_pwd(int fd);
void	cmd_mkdir(int fd, char *arg);

/*
** server
*/

int		create_server(int port);
int		get_cmd(char *str, int fd, char *pwd);
void	handler_serv(int fd);
int		accept_fork(int sock);

/*
** cmd_get_client
*/

void	cmd_get_client(int fd, char *buf);

/*
** cmd_put_client
*/

void	cmd_put_client(int fd, char *buf);

/*
** cmd_client
*/

int		check_permissions_client(char *absolute_path, char *cur_path);
int		cmd_lls(char *arg);
int		cmd_lcd(char *arg, char *absolute_path);
int		cmd_lpwd(void);
int		cmd_lmkdir(char *arg);

/*
** client
*/

int		create_client(char *addr, int port);
void	read_client(int fd, char *buf);
void	wait_user_input_bis(int fd, char *buf, char *pwd);
void	wait_user_input(int fd);

#endif
