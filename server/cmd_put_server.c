/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:44:36 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 15:18:48 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		recv_put_server(int fd, int file, int size_max)
{
	char		*buff;
	int			size;
	int			ret;
	
	ret = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	ft_bzero(buff, size_max);
	while (ret < size_max)
	{
		size = recv(fd, buff + ret, 4096, 0);
		if (size % 4096 != 0)
			break ;
		ret += size;
	}
	write(file, buff, size_max);
	write(file, "\0", 1);
	return (1);
}

int			cmd_put_server(int fd, char *buf)
{
	int			file;
	int			size;

	if ((file = open_file(buf)) == -1)
		return (print_fd_err_int("put [server], can't open this file", fd));
	if ((size = get_size_file(fd)) == -1)
		return (print_fd_err_int("put [server], file doesn't exist", fd));
	if (recv_put_server(fd, file, size) == -1)
		return (print_fd_err_int("put [server], recv failed", fd));
	ft_putendl("\033[32mSUCCESS: put\033[0m");
	ft_putstr("$> ");
	close(file);
	return (1);
}
