/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:44:36 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/09 11:12:39 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void			recv_put_server(int fd, int file, int size_max)
{
	char			*buff;
	int				size;
	int				n;

	n = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return ;
	while (n < size_max)
	{
		size = recv(fd, buff + n, 4096, 0);
		if (size % 4096 != 0)
			break ;
		n += size;
	}
	write(file, buff, size_max);
	close(file);
}

void				cmd_put_server(int fd, char *buf)
{
	int				file;
	int				size;

	if (recv_alert("RDONLY_OK", fd) < 1)
		return (print_error_get_put_server("open() client side failed"));
	if ((file = open_file_wronly(buf, fd)) == -1)
		return (print_error_get_put_server("Can't create the file already exists"));
	if (recv_alert("TEST_OK", fd) < 1)
		return (print_error_get_put_server("Error on server side"));
	if ((size = size_file(fd)) == -1)
		return (print_error_get_put_server("Can't send size from server side"));
	recv_put_server(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	ft_putendl("\033[32mSUCCESS: put\033[0m");
	close(file);
}
