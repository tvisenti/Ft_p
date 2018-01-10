/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:31:59 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/10 11:52:10 by tvisenti         ###   ########.fr       */
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
int     print_error(char *str);
int     create_server(int port);
void    handler_serv(int fd);
int     accept_fork(unsigned int sock);

/*
** cmd_server
*/

int     cmd_ls(int fd);
int		cmd_cd(char *arg);
int		cmd_pwd();
int		cmd_mkdir(char *arg);

#endif
